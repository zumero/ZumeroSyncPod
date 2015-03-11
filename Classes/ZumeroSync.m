//
//  ZumeroSync.m
//
//  ZumeroSync - a simple Objective-C wrapper around the Zumero Client API
//
//  Copyright 2013-2015 Zumero LLC
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

#import "ZumeroSync.h"


@implementation ZumeroSync


#define _US(s)   ((s) ? [(s) UTF8String] : NULL)
#define ZNULLFREE(p)  do { if (p) { zumero_free((void *)p); p = NULL; } } while(0)


#pragma mark - Sync

// Sync the local database with the server database.
//
+ (BOOL) Sync:(NSString *)filename
	cipherKey:(NSString *)cipherKey
	serverUrl:(NSString *)serverUrl
	   remote:(NSString *)remote
   authScheme:(NSDictionary *)authScheme
		 user:(NSString *)user
	 password:(NSString *)password
		error:(NSError **)error
{
	NSString *json = nil;
	
	if (! [ZumeroSync schemeJSON:authScheme json:&json error:error])
		return NO;
	
	return [ZumeroSync Sync:filename cipherKey:cipherKey serverUrl:serverUrl remote:remote authSchemeJS:json user:user password:password error:error];
}


+ (BOOL) Sync:(NSString *)filename
	cipherKey:(NSString *)cipherKey
	serverUrl:(NSString *)serverUrl
	   remote:(NSString *)remote
 authSchemeJS:(NSString *)authSchemeJS
		 user:(NSString *)user
	 password:(NSString *)password
		error:(NSError **)error
{
	char *details = NULL;
	
	int rc = zumero_sync(_US(filename), _US(cipherKey), _US(serverUrl), _US(remote), _US(authSchemeJS), _US(user), _US(password), NULL, &details);
	
	[ZumeroSync logFailure:rc details:details path:filename error:error];
	
	ZNULLFREE(details);
	
	return (rc == 0);
}


#pragma mark - QuarantineSinceLastSync

+ (BOOL) QuarantineSyncLastSync:(NSString *)filename
					  cipherKey:(NSString *)cipherKey
						   pqid:(sqlite3_int64 *)pqid
					      error:(NSError **)error
{
	return [ZumeroSync QuarantineSinceLastSync:filename cipherKey:cipherKey pqid:pqid error:error];
}

+ (BOOL) QuarantineSinceLastSync:(NSString *)filename
					  cipherKey:(NSString *)cipherKey
						   pqid:(sqlite3_int64 *)pqid
					      error:(NSError **)error
{
	char *details = NULL;
	sqlite3_int64 qid = 0;

	int rc = zumero_quarantine_since_last_sync(_US(filename), _US(cipherKey), NULL, &qid, &details);
	
	[ZumeroSync logFailure:rc details:details path:filename error:error];
	
	ZNULLFREE(details);
	
	if (rc == 0)
		*pqid = qid;
	
	return (rc == 0);
}


#pragma mark - SyncQuarantine

//  Sync the local database with the server database, including the changes
//  stored in the specified quarantine.
//
+ (BOOL) SyncQuarantine:(NSString *)filename
			  cipherKey:(NSString *)cipherKey
					qid:(sqlite3_int64)qid
			  serverUrl:(NSString *)serverUrl
				 remote:(NSString *)remote
			 authScheme:(NSDictionary *)authScheme
				   user:(NSString *)user
			   password:(NSString *)password
				partial:(BOOL *)partial
				  error:(NSError **)error
{
	NSString *json = nil;
	
	if (! [ZumeroSync schemeJSON:authScheme json:&json error:error])
		return NO;
	
	return [ZumeroSync SyncQuarantine:filename cipherKey:cipherKey qid:qid serverUrl:serverUrl remote:remote authSchemeJS:json user:user password:password partial:partial error:error];
}

+ (BOOL) SyncQuarantine:(NSString *)filename
			  cipherKey:(NSString *)cipherKey
					qid:(sqlite3_int64)qid
			  serverUrl:(NSString *)serverUrl
				 remote:(NSString *)remote
		   authSchemeJS:(NSString *)authSchemeJS
				   user:(NSString *)user
			   password:(NSString *)password
				partial:(BOOL *)partial
				  error:(NSError **)error
{
	char *details = NULL;
	
	int rc = zumero_sync_quarantine(_US(filename), _US(cipherKey), qid, _US(serverUrl), _US(remote), _US(authSchemeJS), _US(user), _US(password), NULL, &details);
	
	[ZumeroSync logFailure:rc details:details path:filename error:error];
	
	ZNULLFREE(details);
	
	*partial = (rc == ZUMERO_PARTIAL);
	
	return ((rc == 0) || (rc == ZUMERO_PARTIAL));
}


#pragma mark - DeleteQuarantine

//  Permanently delete quarantined changes.
//
+ (BOOL) DeleteQuarantine:(NSString *)filename
				cipherKey:(NSString *)cipherKey
					  qid:(sqlite3_int64)qid
					error:(NSError **)error
{
	char *details = NULL;
	
	int rc = zumero_delete_quarantine(_US(filename), _US(cipherKey), qid, &details);
	
	[ZumeroSync logFailure:rc details:details path:filename error:error];
	
	ZNULLFREE(details);
	
	return (rc == 0);
}


#pragma mark - helpers

+ (BOOL)schemeJSON:(NSDictionary *)scheme json:(NSString **)pJson error:(NSError **)error
{
	NSString *json = nil;
	
	if (scheme)
	{
		NSData *jsdata = [NSJSONSerialization dataWithJSONObject:scheme options:0 error:error];
		if (! jsdata)
		{
			[ZumeroSync logZumeroError:ZUMERO_INVALIDARG text:@"scheme could not be converted to JSON" path:nil error:error];
			return NO;
		}
		
		json = [[NSString alloc] initWithData:jsdata encoding:NSUTF8StringEncoding];
	}
	
	*pJson = json;
	return YES;
}

+ (void) logFailure:(int)rc details:(const char *)details path:(NSString *)path error:(NSError **)error
{
	if ((rc != 0) && (rc != ZUMERO_PARTIAL))
	{
		NSString *msg = nil;
		if (details)
			msg = [NSString stringWithUTF8String:details];
		else
			msg = [NSString stringWithFormat:@"error (%i)", rc];
		
		[ZumeroSync logZumeroError:rc text:msg path:path error:error];
	}
}

+ (void) logZumeroError:(int)zcode text:(NSString *)text path:(NSString *)path error:(NSError **)error
{
	if (*error)
		return;
	
	NSMutableDictionary *ui = [NSMutableDictionary dictionary];
	
	const char *prefix = zumero_errstr(zcode);
	
	if (prefix)
		text = [NSString stringWithFormat:@"%s: %@", prefix, text];
	
	[ui setObject:text forKey:NSLocalizedDescriptionKey];
	
	if (path)
		[ui setObject:path forKey:NSFilePathErrorKey];
	
	NSError *ze = [[NSError alloc]
				   initWithDomain:@"Zumero" code:zcode userInfo:ui
				   ];

	*error = ze;
}


@end

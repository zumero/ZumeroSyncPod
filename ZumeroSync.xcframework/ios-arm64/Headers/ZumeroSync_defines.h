//
//  ZumeroSync_defines.h
//  ZumeroSync
//
//  Created by Troy Stanger on 10/17/24.
//

#ifndef ZumeroSync_defines_h
#define ZumeroSync_defines_h

#import "ZumeroUtil.h"

#include <sqlite3.h>
#include <zumero_client_api.h>

/** provides static methods implementing the Zumero Sync and Quarantine APIs.
 */
@interface ZumeroSync : NSObject

typedef void (^ZumeroProgressCallback) (int, int, int64_t, int64_t, void *);

/** @name Sync
 */

/** Sync the local database with the server database.

 @param filename Database filename (UTF-8)
 @param cipherKey Key to unlock encrypted database (or nil)
 @param serverUrl Zumero server url
 @param remote Dbfile name on server
 @param authSchemeJS Scheme part of auth credentials, as JSON (or nil)
 @param user Username part of auth credentials (or nil)
 @param password Password part of auth credentials (or nil)
 @param error On failure, localizedDescription will contain error text

 @return `YES` if sync was successful
 */
+ (BOOL) Sync:(NSString *)filename
    cipherKey:(NSString *)cipherKey
    serverUrl:(NSString *)serverUrl
       remote:(NSString *)remote
 authSchemeJS:(NSString *)authSchemeJS
         user:(NSString *)user
     password:(NSString *)password
        error:(NSError **)error;


/** Sync the local database with the server database.

 @param filename Database filename (UTF-8)
 @param cipherKey Key to unlock encrypted database (or nil)
 @param serverUrl Zumero server url
 @param remote Dbfile name on server
 @param authScheme Scheme part of auth credentials (or nil)
 @param user Username part of auth credentials (or nil)
 @param password Password part of auth credentials (or nil)
 @param error On failure, localizedDescription will contain error text

 @return `YES` if sync was successful
 */
+ (BOOL) Sync:(NSString *)filename
    cipherKey:(NSString *)cipherKey
    serverUrl:(NSString *)serverUrl
       remote:(NSString *)remote
   authScheme:(NSDictionary *)authScheme
         user:(NSString *)user
     password:(NSString *)password
        error:(NSError **)error;

/** Sync the local database with the server database.

 @param filename Database filename (UTF-8)
 @param cipherKey Key to unlock encrypted database (or nil)
 @param serverUrl Zumero server url
 @param remote Dbfile name on server
 @param authSchemeJS Scheme part of auth credentials, as JSON (or nil)
 @param user Username part of auth credentials (or nil)
 @param password Password part of auth credentials (or nil)
 @param callback A progress/cancellation callback block (or nil)
 @param dataPointer An opaque data pointer for use by the callback block
 @param error On failure, localizedDescription will contain error text

 @return `YES` if sync was successful
 */
+ (BOOL) Sync:(NSString *)filename
    cipherKey:(NSString *)cipherKey
    serverUrl:(NSString *)serverUrl
       remote:(NSString *)remote
 authSchemeJS:(NSString *)authSchemeJS
         user:(NSString *)user
     password:(NSString *)password
     callback:(ZumeroProgressCallback)callback
  dataPointer:(void*)dataPointer
        error:(NSError **)error;


/** Sync the local database with the server database.

 @param filename Database filename (UTF-8)
 @param cipherKey Key to unlock encrypted database (or nil)
 @param serverUrl Zumero server url
 @param remote Dbfile name on server
 @param authScheme Scheme part of auth credentials (or nil)
 @param user Username part of auth credentials (or nil)
 @param password Password part of auth credentials (or nil)
 @param callback A progress/cancellation callback block (or nil)
 @param dataPointer An opaque data pointer for use by the callback block
 @param error On failure, localizedDescription will contain error text

 @return `YES` if sync was successful
 */
+ (BOOL) Sync:(NSString *)filename
    cipherKey:(NSString *)cipherKey
    serverUrl:(NSString *)serverUrl
       remote:(NSString *)remote
   authScheme:(NSDictionary *)authScheme
         user:(NSString *)user
     password:(NSString *)password
     callback:(ZumeroProgressCallback)callback
  dataPointer:(void*)dataPointer
        error:(NSError **)error;

/** Sync the local database with the server database.

 @param filename Database filename (UTF-8)
 @param cipherKey Key to unlock encrypted database (or nil)
 @param serverUrl Zumero server url
 @param remote Dbfile name on server
 @param authSchemeJS Scheme part of auth credentials, as JSON (or nil)
 @param user Username part of auth credentials (or nil)
 @param password Password part of auth credentials (or nil)
 @param callback A progress/cancellation callback block (or nil)
 @param dataPointer An opaque data pointer for use by the callback block
 @param optionsJS JSON string specifying additional sync options (or nil)
 @param syncId receives a sync details lookup token, if requested in optionsJS
 @param error On failure, localizedDescription will contain error text

 @return `YES` if sync was successful
 */
+ (BOOL) Sync:(NSString *)filename
    cipherKey:(NSString *)cipherKey
    serverUrl:(NSString *)serverUrl
       remote:(NSString *)remote
 authSchemeJS:(NSString *)authSchemeJS
         user:(NSString *)user
     password:(NSString *)password
     callback:(ZumeroProgressCallback)callback
  dataPointer:(void*)dataPointer
    optionsJS:(NSString *)optionsJS
       syncId:(int *)syncId
        error:(NSError **)error;


/** Sync the local database with the server database.

 @param filename Database filename (UTF-8)
 @param cipherKey Key to unlock encrypted database (or nil)
 @param serverUrl Zumero server url
 @param remote Dbfile name on server
 @param authScheme Scheme part of auth credentials (or nil)
 @param user Username part of auth credentials (or nil)
 @param password Password part of auth credentials (or nil)
 @param callback A progress/cancellation callback block (or nil)
 @param dataPointer An opaque data pointer for use by the callback block
 @param options additional sync options (or nil)
 @param syncId receives a sync details lookup token, if requested in options
 @param error On failure, localizedDescription will contain error text

 @return `YES` if sync was successful
 */
+ (BOOL) Sync:(NSString *)filename
    cipherKey:(NSString *)cipherKey
    serverUrl:(NSString *)serverUrl
       remote:(NSString *)remote
   authScheme:(NSDictionary *)authScheme
         user:(NSString *)user
     password:(NSString *)password
     callback:(ZumeroProgressCallback)callback
  dataPointer:(void*)dataPointer
      options:(NSDictionary *)options
       syncId:(int *)syncId
        error:(NSError **)error;

/** @name Cancel
 */

/**  Cancel a sync that is currently in progress.

 @param cancellationToken The cancellation token that was passed the the ZumeroProgressCallback for the current sync
 */
+ (void) Cancel:(int)cancellationToken;

/** @name Quarantine
 */

/**  Move un-synced local changes into an isolated holding area. Typically, the
 reason to do so is because the local changes conflict with other changes
 already on the server.

 The quarantined changes are stored locally, so no network activity is
 required.

 @param filename Database filename (UTF-8)
 @param cipherKey Key to unlock encrypted database (or nil)
 @param optionsJS JSON string specifying additional quarantine options (or nil)
 @param pqid OUT: quarantine id written here
 @param error On failure, localizedDescription will contain error text

 @return `YES` if quarantine was successful
 */

+ (BOOL) QuarantineSinceLastSync:(NSString *)filename
                       cipherKey:(NSString *)cipherKey
                         options:(NSDictionary *)options
                            pqid:(sqlite3_int64 *)pqid
                           error:(NSError **)error;

/** @name Quarantine
 */

/**  Move un-synced local changes into an isolated holding area. Typically, the
 reason to do so is because the local changes conflict with other changes
 already on the server.

 The quarantined changes are stored locally, so no network activity is
 required.

 @param filename Database filename (UTF-8)
 @param cipherKey Key to unlock encrypted database (or nil)
 @param options additional quarantine options (or nil)
 @param pqid OUT: quarantine id written here
 @param error On failure, localizedDescription will contain error text

 @return `YES` if quarantine was successful
 */

+ (BOOL) QuarantineSinceLastSync:(NSString *)filename
                       cipherKey:(NSString *)cipherKey
                       optionsJS:(NSString *)optionsJS
                            pqid:(sqlite3_int64 *)pqid
                           error:(NSError **)error;

/**  Move un-synced local changes into an isolated holding area. Typically, the
 reason to do so is because the local changes conflict with other changes
 already on the server.

 The quarantined changes are stored locally, so no network activity is
 required.

 @param filename Database filename (UTF-8)
 @param cipherKey Key to unlock encrypted database (or nil)
 @param pqid OUT: quarantine id written here
 @param error On failure, localizedDescription will contain error text

 @return `YES` if quarantine was successful
 */
+ (BOOL) QuarantineSinceLastSync:(NSString *)filename
                       cipherKey:(NSString *)cipherKey
                            pqid:(sqlite3_int64 *)pqid
                           error:(NSError **)error;

// older, incorrect name, left here for compatibility
+ (BOOL) QuarantineSyncLastSync:(NSString *)filename
                      cipherKey:(NSString *)cipherKey
                           pqid:(sqlite3_int64 *)pqid
                          error:(NSError **)error __deprecated;

/** Sync the local database with the server database, including the changes
 stored in the specified quarantine.

 @param filename Database filename (UTF-8)
 @param cipherKey Key to unlock encrypted database (or nil)
 @param qid quarantine id from which to sync
 @param serverUrl Zumero server url
 @param remote Dbfile name on server
 @param authScheme Scheme part of auth credentials (or nil)
 @param user Username part of auth credentials (or nil)
 @param password Password part of auth credentials (or nil)
 @param partial OUT: YES if SyncQuarantine must be called again
 @param error On failure, localizedDescription will contain error text

 @return `YES` if sync was successful
 */
+ (BOOL) SyncQuarantine:(NSString *)filename
              cipherKey:(NSString *)cipherKey
                    qid:(sqlite3_int64)qid
              serverUrl:(NSString *)serverUrl
                 remote:(NSString *)remote
             authScheme:(NSDictionary *)authScheme
                   user:(NSString *)user
               password:(NSString *)password
                partial:(BOOL *)partial
                  error:(NSError **)error;

/** Sync the local database with the server database, including the changes
 stored in the specified quarantine.

 @param filename Database filename (UTF-8)
 @param cipherKey Key to unlock encrypted database (or nil)
 @param qid quarantine id from which to sync
 @param serverUrl Zumero server url
 @param remote Dbfile name on server
 @param authSchemeJS Scheme part of auth credentials, as JSON (or nil)
 @param user Username part of auth credentials (or nil)
 @param password Password part of auth credentials (or nil)
 @param partial OUT: YES if SyncQuarantine must be called again
 @param error On failure, localizedDescription will contain error text

 @return `YES` if sync was successful
 */
+ (BOOL) SyncQuarantine:(NSString *)filename
              cipherKey:(NSString *)cipherKey
                    qid:(sqlite3_int64)qid
              serverUrl:(NSString *)serverUrl
                 remote:(NSString *)remote
           authSchemeJS:(NSString *)authSchemeJS
                   user:(NSString *)user
               password:(NSString *)password
                partial:(BOOL *)partial
                  error:(NSError **)error;

/** Sync the local database with the server database, including the changes
 stored in the specified quarantine.

 @param filename Database filename (UTF-8)
 @param cipherKey Key to unlock encrypted database (or nil)
 @param qid quarantine id from which to sync
 @param serverUrl Zumero server url
 @param remote Dbfile name on server
 @param authScheme Scheme part of auth credentials (or nil)
 @param user Username part of auth credentials (or nil)
 @param password Password part of auth credentials (or nil)
 @param callback A progress/cancellation callback block (or nil)
 @param dataPointer An opaque data pointer for use by the callback block
 @param options additional sync options (or nil)
 @param syncId receives a sync details lookup token, if requested in options
 @param partial OUT: YES if SyncQuarantine must be called again
 @param error On failure, localizedDescription will contain error text

 @return `YES` if sync was successful
 */
+ (BOOL) SyncQuarantine:(NSString *)filename
              cipherKey:(NSString *)cipherKey
                    qid:(sqlite3_int64)qid
              serverUrl:(NSString *)serverUrl
                 remote:(NSString *)remote
             authScheme:(NSDictionary *)authScheme
                   user:(NSString *)user
               password:(NSString *)password
               callback:(ZumeroProgressCallback)callback
            dataPointer:(void*)dataPointer
                options:(NSDictionary *)options
                 syncId:(int *)syncId
                partial:(BOOL *)partial
                  error:(NSError **)error;

/** Sync the local database with the server database, including the changes
 stored in the specified quarantine.

 @param filename Database filename (UTF-8)
 @param cipherKey Key to unlock encrypted database (or nil)
 @param qid quarantine id from which to sync
 @param serverUrl Zumero server url
 @param remote Dbfile name on server
 @param authSchemeJS Scheme part of auth credentials, as JSON (or nil)
 @param user Username part of auth credentials (or nil)
 @param password Password part of auth credentials (or nil)
 @param callback A progress/cancellation callback block (or nil)
 @param dataPointer An opaque data pointer for use by the callback block
 @param optionsJS JSON string specifying additional sync options (or nil)
 @param syncId receives a sync details lookup token, if requested in optionsJS
 @param partial OUT: YES if SyncQuarantine must be called again
 @param error On failure, localizedDescription will contain error text

 @return `YES` if sync was successful
 */
+ (BOOL) SyncQuarantine:(NSString *)filename
              cipherKey:(NSString *)cipherKey
                    qid:(sqlite3_int64)qid
              serverUrl:(NSString *)serverUrl
                 remote:(NSString *)remote
           authSchemeJS:(NSString *)authSchemeJS
                   user:(NSString *)user
               password:(NSString *)password
               callback:(ZumeroProgressCallback)callback
            dataPointer:(void*)dataPointer
              optionsJS:(NSString *)optionsJS
                 syncId:(int *)syncId
                partial:(BOOL *)partial
                  error:(NSError **)error;


/**  Permanently delete quarantined changes.

 @param filename Database filename (UTF-8)
 @param cipherKey Key to unlock encrypted database (or nil)
 @param qid Quarantine id
 @param error On failure, localizedDescription will contain error text

 @return `YES` if the changes were deleted
 */
+ (BOOL) DeleteQuarantine:(NSString *)filename
                cipherKey:(NSString *)cipherKey
                      qid:(sqlite3_int64)qid
                    error:(NSError **)error;

/**  Permanently delete quarantined changes.

 @param filename Database filename (UTF-8)
 @param cipherKey Key to unlock encrypted database (or nil)
 @param qid Quarantine id
 @param options additional quarantine options (or nil)
 @param error On failure, localizedDescription will contain error text

 @return `YES` if the changes were deleted
 */
+ (BOOL) DeleteQuarantine:(NSString *)filename
                cipherKey:(NSString *)cipherKey
                      qid:(sqlite3_int64)qid
                  options:(NSDictionary *)options
                    error:(NSError **)error;

/**  Permanently delete quarantined changes.

 @param filename Database filename (UTF-8)
 @param cipherKey Key to unlock encrypted database (or nil)
 @param qid Quarantine id
 @param optionsJS JSON string specifying additional quarantine options (or nil)
 @param error On failure, localizedDescription will contain error text

 @return `YES` if the changes were deleted
 */
+ (BOOL) DeleteQuarantine:(NSString *)filename
                cipherKey:(NSString *)cipherKey
                      qid:(sqlite3_int64)qid
                optionsJS:(NSString *)optionsJS
                    error:(NSError **)error;

@end


#endif /* ZumeroSync_defines_h */

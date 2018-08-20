//
//  ZumeroUtil.m
//  ZumeroSync
//
//  Copyright 2013-2018 Zumero LLC
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

#import "ZumeroUtil.h"

#define FORMATTED_UUID_LEN 36

#define hexval(c)  ((unsigned char)(isdigit(c) ? ((c) - '0') : (tolower(c) + 10 - 'a')))
#define hexByte(p) ((hexval((p)[0]) << 4) | hexval((p)[1]))

# include <stdint.h>
typedef uint8_t       SG_uint8;

char * SG_hex__format_uint8(char * pbuf, SG_uint8 v);


@implementation ZumeroUtil

//  given a 16-byte blob (in NSData form), return an MSSQL-style
//  GUID string ("aaba1234-5678-9090-9876-aabbccdd1234")
//
+ (NSString *) dataToSqlGuid:(NSData *)uuid
{
	if ((! uuid) || ([uuid length] != 16))
		return nil;
	
	char buf[FORMATTED_UUID_LEN + 1];
	
	const unsigned char *blob = [uuid bytes];

	SG_hex__format_uint8(buf + 0, blob[3]);
    SG_hex__format_uint8(buf + 2, blob[2]);
    SG_hex__format_uint8(buf + 4, blob[1]);
    SG_hex__format_uint8(buf + 6, blob[0]);
    buf[8] = '-';
    SG_hex__format_uint8(buf + 9, blob[5]);
    SG_hex__format_uint8(buf + 11, blob[4]);
    buf[13] = '-';
    SG_hex__format_uint8(buf + 14, blob[7]);
    SG_hex__format_uint8(buf + 16, blob[6]);
    buf[18] = '-';
    SG_hex__format_uint8(buf + 19, blob[8]);
    SG_hex__format_uint8(buf + 21, blob[9]);
    buf[23] = '-';
    SG_hex__format_uint8(buf + 24, blob[10]);
    SG_hex__format_uint8(buf + 26, blob[11]);
    SG_hex__format_uint8(buf + 28, blob[12]);
    SG_hex__format_uint8(buf + 30, blob[13]);
    SG_hex__format_uint8(buf + 32, blob[14]);
    SG_hex__format_uint8(buf + 34, blob[15]);
    buf[36] = 0;
	
	return [NSString stringWithUTF8String:buf];
}

//  given an MSSQL-style GUID string ("aaba1234-5678-9090-9876-aabbccdd1234"),
//  return the corresponding 16-byte blob
//
+ (NSData *) sqlGuidToData:(NSString *)sqlguid
{
	if (! sqlguid)
		return nil;

	NSError *err = nil;
	NSRegularExpression *re = [NSRegularExpression regularExpressionWithPattern:@"[0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12}\\s*$" options:NSRegularExpressionCaseInsensitive error:&err];
	
	NSUInteger n = [re numberOfMatchesInString:sqlguid options:NSMatchingAnchored range:NSMakeRange(0, [sqlguid length])];
	
	if (n != 1)
		return nil;
	
	unsigned char bytes[16];
    const char *st = [sqlguid UTF8String];

    bytes[3] = hexByte(st + 0);
    bytes[2] = hexByte(st + 2);
    bytes[1] = hexByte(st + 4);
    bytes[0] = hexByte(st + 6);
    bytes[5] = hexByte(st + 9);
    bytes[4] = hexByte(st + 11);
    bytes[7] = hexByte(st + 14);
    bytes[6] = hexByte(st + 16);
    bytes[8] = hexByte(st + 19);
    bytes[9] = hexByte(st + 21);
    bytes[10] = hexByte(st + 24);
    bytes[11] = hexByte(st + 26);
    bytes[12] = hexByte(st + 28);
    bytes[13] = hexByte(st + 30);
    bytes[14] = hexByte(st + 32);
    bytes[15] = hexByte(st + 34);

    return [NSData dataWithBytes:bytes length:16];
}


@end

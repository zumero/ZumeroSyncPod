/*
 *   Copyright 2013-2016 Zumero LLC
 * 
 *   Licensed under the Zumero Client SDK License (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 * 
 *      http://zumero.com/dev-center/zss/sdk-license/
 * 
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 */

#ifndef _ZUMERO_CLIENT_API_H_
#define _ZUMERO_CLIENT_API_H_

#if !defined(WINDOWS)
#include <stdint.h>
#endif

/*
** Make sure we can call this stuff from C++.
*/
#ifdef __cplusplus
extern "C" {
#endif

/*
** Result Codes
**
** Most Zumero functions return an integer result code to indicate success or
** failure. In some cases, that result code may be a SQLite result code.
** Or, it may be a Zumero-specific result code defined below.
**
** The zumero_errstr() function can be used to obtain an English-language
** string corresponding to any Zumero-specific result code.
**
** WARNING: If you change the numeric value of any result code, you must also
**          change the desktop/Xamarin wrapper to match:
**              @/src/sdk/netfx/zumero.cs
**          If you add or remove result codes, then you'll need to change
**          that wrapper as well as the WinRT/WP8 wrappers:
**              @/src/sdk/windows/shared/client_component/ZumeroClient.h
**              @/src/sdk/windows/shared/client_netfx/ZumeroClient.cs
*/

#define ZUMERO_ERROR    200              /* low byte of any result code which is an error */
#define ZUMERO_PARTIAL  201              /* no longer returned by any zumero functions */

#define ZUMERO_NETWORK_CONNECTION_FAILED         (ZUMERO_ERROR | (1<<8))
#define ZUMERO_AUTHENTICATION_FAILED             (ZUMERO_ERROR | (2<<8))
#define ZUMERO_PERMISSION_DENIED                 (ZUMERO_ERROR | (3<<8))
#define ZUMERO_HTTP_400                          (ZUMERO_ERROR | (4<<8))
#define ZUMERO_HTTP_406                          (ZUMERO_ERROR | (5<<8))
#define ZUMERO_HTTP_500                          (ZUMERO_ERROR | (6<<8))
#define ZUMERO_HTTP_404                          (ZUMERO_ERROR | (7<<8))
#define ZUMERO_HTTP_502                          (ZUMERO_ERROR | (8<<8))
#define ZUMERO_HTTP_OTHER                        (ZUMERO_ERROR | (9<<8))
#define ZUMERO_CONSTRAINT_VIOLATION              (ZUMERO_ERROR | (10<<8))
#define ZUMERO_UNIQUE_CONSTRAINT_VIOLATION       (ZUMERO_ERROR | (11<<8))
#define ZUMERO_CHECK_CONSTRAINT_VIOLATION        (ZUMERO_ERROR | (12<<8))
#define ZUMERO_FOREIGN_KEY_CONSTRAINT_VIOLATION  (ZUMERO_ERROR | (13<<8))
#define ZUMERO_SYNC_REJECT_BY_RULE               (ZUMERO_ERROR | (14<<8))
#define ZUMERO_WRONG_DBFILE                      (ZUMERO_ERROR | (15<<8))
#define ZUMERO_SERVER_ROLLBACK_DETECTED          (ZUMERO_ERROR | (16<<8))
#define ZUMERO_DBFILE_NOT_FOUND                  (ZUMERO_ERROR | (17<<8))
#define ZUMERO_TOO_MANY_DEADLOCKS                (ZUMERO_ERROR | (18<<8))
#define ZUMERO_LICENSE_ERROR                     (ZUMERO_ERROR | (19<<8))
#define ZUMERO_CLIENT_CORRUPTION_DETECTED        (ZUMERO_ERROR | (20<<8))
#define ZUMERO_SERVER_MISCONFIGURATION           (ZUMERO_ERROR | (21<<8))
#define ZUMERO_PURGED_DATA_REFERENCED            (ZUMERO_ERROR | (22<<8))
#define ZUMERO_INVALIDARG                        (ZUMERO_ERROR | (30<<8))
#define ZUMERO_INVALID_DBFILE_NAME               (ZUMERO_ERROR | (50<<8))
#define ZUMERO_INVALID_AUTH_SCHEME_STRING        (ZUMERO_ERROR | (51<<8))
#define ZUMERO_UNSUPPORTED                       (ZUMERO_ERROR | (52<<8))
#define ZUMERO_DIFFERENT_CREDENTIALS             (ZUMERO_ERROR | (53<<8))
#define ZUMERO_CANCELLED                         (ZUMERO_ERROR | (54<<8))


/*
** The possible values for the phase indicator 
** for a zumero_progress_callback function.
*/
#define ZUMERO_PHASE_PREPARING              1 /* Examining the local sqlite database  
                                                 to determine which changes need to be 
                                                 uploaded. */
#define ZUMERO_PHASE_UPLOADING              2 /* Uploading changes to the server. */
#define ZUMERO_PHASE_WAITING_FOR_RESPONSE   3 /* Waiting for the server to apply our 
                                                 changes and calculate the response. */
#define ZUMERO_PHASE_DOWNLOADING            4 /* Downloading the changes from the server. */
#define ZUMERO_PHASE_APPLYING               5 /* Applying the downloaded changes. */

#if defined(WINDOWS)
    typedef __int64					zumero_int64;
#else
    typedef int64_t					zumero_int64;
#endif

/*
** The prototype for the progress funciton used by zumero_sync2.
*/
typedef void zumero_progress_callback(
  int cancellation_token,    /* The cancellation token for this sync operation.
                                The cancellation token will remain the same 
                                for all progress callbacks for a single sync 
                                operation. */
  int phase,                 /* The current sync phase. You may receive 
                                multiple progress callbacks for the same 
                                phase. Some phases may be repeated multiple 
                                times for a single sync operation.  See the 
                                ZUMERO_PHASE_* definitions for the possible 
                                values of this argument. */
  zumero_int64 bytesSoFar,   /* If the phase is ZUMERO_PHASE_UPLOADING or 
                                ZUMERO_PHASE_DOWNLOADING, this argument 
                                will be the number of bytes that have been 
                                transferred so far.*/
  zumero_int64 bytesTotal,   /* If the phase is ZUMERO_PHASE_UPLOADING or 
                                ZUMERO_PHASE_DOWNLOADING, this argument 
                                will be the number of bytes that will be 
                                transferred in this phase.*/
  void* data                 /* An opaque data pointer. You can provide 
                                this to zumero_sync2, and zumero will not
                                modify or use it. */
  );

/*
** Sync the local database with the server database.
*/
int zumero_sync(
  const char *zFilename,     /* Database filename (UTF-8) */
  const char *zCipherKey,    /* Key to unlock encrypted database */
  const char *zServerUrl,    /* Zumero server url */
  const char *zDbfile,       /* Dbfile name on server */
  const char *zAuthScheme,   /* Scheme part of auth credentials */
  const char *zUser,         /* Username part of auth credentials */
  const char *zPassword,     /* Password part of auth credentials */
  const char *zTempDir,      /* Temp directory filename */
  char **pzErrorDetails      /* OUT: Error message written here */
);


/*
** Sync the local database with the server database. This version supports 
** a progress callback function.
*/
int zumero_sync2(
    const char *zFilename,     /* Database filename (UTF-8) */
    const char *zCipherKey,    /* Key to unlock encrypted database */
    const char *zServerUrl,    /* Zumero server url */
    const char *zDbfile,       /* Dbfile name on server */
    const char *zAuthScheme,   /* Scheme part of auth credentials */
    const char *zUser,         /* Username part of auth credentials */
    const char *zPassword,     /* Password part of auth credentials */
    const char *zTempDir,      /* Temp directory filename */
    zumero_progress_callback * fnCallback, /* Callback function */
    void * pCallbackData,      /* A pointer, which will be passed to the zumero_progress_callback function */
    char **pzErrorDetails      /* OUT: Error message written here */
    );

/*
** Sync the local database with the server database. This version supports 
** optional JSON configuration detais.
*/
int zumero_sync3(
  const char *zFilename,     /* Database filename (UTF-8) */
  const char *zCipherKey,    /* Key to unlock encrypted database */
  const char *zServerUrl,    /* Zumero server url */
  const char *zDbfile,       /* Dbfile name on server */
  const char *zAuthScheme,   /* Scheme part of auth credentials */
  const char *zUser,         /* Username part of auth credentials */
  const char *zPassword,     /* Password part of auth credentials */
  const char *zTempDir,      /* Temp directory filename */
  zumero_progress_callback * fnCallback, /* Callback function */
  void * pCallbackData,      /* A pointer, which will be passed to the zumero_progress_callback function */
  const char *jsOptions,     /* JSON string with additional options */
  int *pSyncId,              /* OUT: sync details id (may be NULL) */
  char **pzErrorDetails      /* OUT: Error message written here */
);

/*
** Move un-synced local changes into an isolated holding area. Typically, the
** reason to do so is because the local changes conflict with other changes
** already on the server.
**
** The quarantined changes are stored locally, so no network activity is
** required.
*/
int zumero_quarantine_since_last_sync(
  const char *zFilename,     /* Database filename (UTF-8) */
  const char *zCipherKey,    /* Key to unlock encrypted database */
  const char *zTempDir,      /* Temp directory filename */
  zumero_int64* pnQid,       /* OUT: quarantine id written here */
  char **pzErrorDetails      /* OUT: Error message written here */
);

/*
** Sync the local database with the server database, including the changes
** stored in the specified quarantine.
*/
int zumero_sync_quarantine(
  const char *zFilename,     /* Database filename (UTF-8) */
  const char *zCipherKey,    /* Key to unlock encrypted database */
  zumero_int64 qid,          /* Quarantine id */
  const char *zServerUrl,    /* Zumero server url */
  const char *zDbfile,       /* Dbfile name on server */
  const char *zAuthScheme,   /* Scheme part of auth credentials */
  const char *zUser,         /* Username part of auth credentials */
  const char *zPassword,     /* Password part of auth credentials */
  const char *zTempDir,      /* Temp directory filename */
  char **pzErrorDetails      /* OUT: Error message written here */
);

int zumero_sync_quarantine3(
  const char *zFilename,     /* Database filename (UTF-8) */
  const char *zCipherKey,    /* Key to unlock encrypted database */
  zumero_int64 qid,          /* Quarantine id */
  const char *zServerUrl,    /* Zumero server url */
  const char *zDbfile,       /* Dbfile name on server */
  const char *zAuthScheme,   /* Scheme part of auth credentials */
  const char *zUser,         /* Username part of auth credentials */
  const char *zPassword,     /* Password part of auth credentials */
  const char *zTempDir,      /* Temp directory filename */
  zumero_progress_callback * fnCallback, /* Progress callback function */
  void * pCallbackData,      /* A pointer, which will be passed to the zumero_progress_callback function */
  const char *jsOptions,     /* JSON string with additional options */
  int *pSyncId,              /* OUT: sync details id (may be NULL) */
  char **pzErrorDetails      /* OUT: Error message written here */
);

/*
** Permanently delete quarantined changes.
*/
int zumero_delete_quarantine(
  const char *zFilename,     /* Database filename (UTF-8) */
  const char *zCipherKey,    /* Key to unlock encrypted database */
  zumero_int64 qid,          /* Quarantine id */
  char **pzErrorDetails      /* OUT: Error message written here */
);

/*
** Free memory stored in a pointer returned from a Zumero function.
*/
void zumero_free(void*);

/*
** Return the English-language text that describes the result code.
*/
const char* zumero_errstr(int);

/*
** Cancel a zumero_sync call that is in progress. The cancellationToken 
** will be provided to your callback function. This function is safe to call from
** any thread. The zumero_sync call will throw a ZUMERO_CANCELLED error.
*/
void zumero_cancel(int cancellationToken);

#ifdef __cplusplus
}  /* End of the 'extern "C"' block */
#endif
#endif

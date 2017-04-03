# ZumeroSync CHANGELOG

## 3.0.1.3598

- Update to ZSS 3.0.1 client libraries

## 3.0.0.3471

- Update to ZSS 3.0.0 libraries

## 2.3.0.3231

- Update to ZSS 2.3.0 libraries
- Adds support for the Sync Details retrieval. See http://zumero.com/docs/zumero_for_sql_server_client_api.html#sync_details for details.

## 2.2.2.3164

- Update to ZSS 2.2.2 libraries
- The iOS pod now reports the correct version number in stack traces

## 2.2.1.3091

- Increase download timeout during sync

## 2.2.0.3064

- Update to ZSS 2.2.0 libraries

## 2.1.0.2940

- Make sure Cocoapods knows this pod is iOS and Mac-compatible
- Include bitcode in iOS library

## 2.1.0.2939

- Updated to ZSS 2.1.0 libraries
- Added optional Sync progress and cancellation callbacks. See http://zumero.com/docs/zumero_for_sql_server_client_api.html#section_progress for details

## 2.0.1.2640

- Updated to ZSS 2.0.1 libraries.

## 2.0.0.2589

- Updated to ZSS 2.0 libraries. 
- This is a significant upgrade, and should only be used with ZSS 2.x servers. Older clients will work with ZSS 2.x servers, but newer client libraries are *not* backwards compatible.
- Please see the ZSS upgrade tutorial at http://zumero.com/howto/zss-upgrade/ for details on the recommended upgrade path.
- To maintain compatibility with ZSS 1.x servers, append `, '~> 1.5'` to the `ZumeroSync` line in your Podfile.

## 1.5.0.2157

- Updated to ZSS 1.5 libraries

## 1.4.0.2014

- Xcode 6 build fixes
- Updated to ZSS 1.4 libraries

## 1.3.0.1880

- Updated to ZSS 1.3 libraries

## 1.2.0.1800

- Added 64-bit iOS emulator libraries

## 1.2.0.1792

- Updated to ZSS 1.2 libraries

## 1.1.1.1749

- Fixed an issue in 1.1 related to tables with multiple UNIQUE constraints

## 1.1.0.1729

- Added social_media link
- Updated with ZSS v1.1 libraries and headers

## 1.0.1.1597

- Update license info in zumero_client_api.h

## 1.0.1.1596

- Encryption keys are now handled properly when synching SQLCipher-encrypted dbfiles
- Clients now get an informative error message for invalid or expired license keys, not just a generic HTTP 500.

## 1.0.0.1556

Initial release.


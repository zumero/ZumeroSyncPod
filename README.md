# ZumeroSync

[![Version](http://cocoapod-badges.herokuapp.com/v/ZumeroSync/badge.png)](http://cocoadocs.org/docsets/ZumeroSync)
[![Platform](http://cocoapod-badges.herokuapp.com/p/ZumeroSync/badge.png)](http://cocoadocs.org/docsets/ZumeroSync)

Objective-C methods for synching local database files with SQL Server databases.

[Zumero for SQL Server][zss] (ZSS) allows you to synchronize a SQLite database file with data stored in MS SQL Server.  This enables your app to keep a local/offline copy of your server-side data and interact with it using the familiar and ubiquitous SQLite library.  Zumero will synchronize the local SQLite data with the remote SQL Server data.  Zumero takes care of two-way synchronization, translating data types, verifying permissions, and handling conflicts.

This extension includes code from the ZSS Client SDK, which is freely available.  It contains the client-side code necessary to sync with a ZSS Server, which is an IIS add-on that must ultimately be purchased and installed on your own server infrastructure.  The ZSS Server then communicates with your SQL Server as needed.

## Usage

See the [installation][started] guide at zumero.com for details on setting up Zumero for SQL Server; this client library requires a server with which to sync.

## Requirements

- An available instance of Zumero for SQL Server
- iOS 6 or later, or
- Mac OS 10.6 or later

## Installation

ZumeroSync is available through [CocoaPods](http://cocoapods.org). To install
it simply add the following line to your Podfile:

    pod "ZumeroSync"

By default, the official [SQLite][sqlitepod] pod will be used for database access.  

To use encrypted local storage on iOS, use [SQLCipher][sqlcipherpod] instead; including:

    pod "ZumeroSync/SQLCipher"

instead of the default `pod` reference will include SQLCipher.

## Version 3.x

This is a significant upgrade, and should only be used with ZSS 3.x servers. Older clients will work with ZSS 3.x servers, but newer client libraries are *not* backwards compatible.

Please see the ZSS upgrade tutorial at [zumero.com/howto/zss-upgrade](http://zumero.com/howto/zss-upgrade/) for details on the recommended upgrade path.

To maintain compatibility with ZSS 1.x servers, append `, '~> 1.5'` to the `ZumeroSync` line in your Podfile, e.g.

    pod 'ZumeroSync', '~> 1.5'

For ZSS 2.x servers, append `, '~> 2.3'` instead, e.g.:

    pod 'ZumeroSync', '~> 2.3'

## Author

Zumero LLC, <support@zumero.com>

## License

ZumeroSync is available under the Apache license (v2). See the LICENSE file for more info.

[started]: http://zumero.com/docs/zumero_for_sql_server_install.html
[zss]: http://zumero.com/dev-center/zss/
[sqlcipherpod]: https://github.com/guilhermeandrade/sqlcipher
[sqlitepod]: https://github.com/CocoaPods/Specs/tree/master/sqlite3

Pod::Spec.new do |s|
  s.name         = "ZumeroSync"
  s.version      = "3.2.0.4154"
  s.summary      = "Use Zumero to sync SQL Server databases with local SQLite dbfiles."
  s.description  = <<-DESC
                    Includes all sync and quarantine functions of the Zumero API.

                    Zumero syncs local (SQLite) databases bidirectionally with backend SQL Server databases.
                   DESC
  s.homepage     = "http://zumero.com/dev-center/zss"
  s.license      = 'Apache'
  s.author       = { "Zumero LLC" => "support@zumero.com" }
  s.source       = { :git => "https://github.com/zumero/ZumeroSyncPod.git", :tag => s.version.to_s }
  s.social_media_url = 'https://twitter.com/zumero_uno'

  s.requires_arc = true

  s.default_subspec = 'SQLite'
  s.osx.deployment_target = "10.7"
  s.ios.deployment_target = '7.0'

  s.subspec 'SQLite' do |ss|
    ss.dependency 'sqlite3'

    ss.libraries = 'z'
    ss.frameworks = 'CFNetwork'
    ss.ios.vendored_library = 'Libraries/ios/libzumero_client_api.a'
    ss.osx.vendored_library = 'Libraries/osx/libzumero_client_api.a'

    ss.source_files = 'Classes'

    ss.ios.exclude_files = 'Classes/osx'
    ss.osx.exclude_files = 'Classes/ios'
  end

  s.subspec 'SQLCipher' do |ss|
    ss.dependency 'SQLCipher'

    ss.libraries = 'z'
    ss.frameworks = 'CFNetwork'
    ss.ios.vendored_library = 'Libraries/ios/libzumero_client_api.a'
    ss.osx.vendored_library = 'Libraries/osx/libzumero_client_api.a'

    ss.source_files = 'Classes'

    ss.ios.exclude_files = 'Classes/osx'
    ss.osx.exclude_files = 'Classes/ios'
  end
end

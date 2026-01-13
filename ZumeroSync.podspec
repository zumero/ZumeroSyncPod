Pod::Spec.new do |s|
  s.name         = "ZumeroSync"
  s.version      = "3.4.0.4917"
  s.summary      = "Use Zumero to sync SQL Server databases with local SQLite dbfiles."
  s.description  = <<-DESC
                    Includes all sync and quarantine functions of the Zumero API.

                    Zumero syncs local (SQLite) databases bidirectionally with backend SQL Server databases.
                   DESC
  s.homepage     = "http://zumero.com/dev-center"
  s.license      = 'Apache'
  s.author       = { "Zumero LLC" => "support@zumero.com" }
  s.source       = { :git => "https://github.com/zumero/ZumeroSyncPod.git", :tag => s.version.to_s }
  s.social_media_url = 'https://twitter.com/zumero_uno'

  s.requires_arc = true

  s.default_subspec = 'SQLite'
  s.osx.deployment_target = "11.0"
  s.ios.deployment_target = '14.0'
  
  s.vendored_frameworks = "ZumeroSync.xcframework"
  s.libraries = 'z'
  s.frameworks = 'CFNetwork'
  
  s.subspec 'SQLite' do |ss|
    ss.dependency 'sqlite3'
  end

  s.subspec 'SQLCipher' do |ss|
    ss.dependency 'SQLCipher'
  end
end

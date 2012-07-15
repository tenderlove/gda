# -*- ruby -*-

require 'rubygems'
require 'hoe'

Hoe.plugins.delete :rubyforge
Hoe.plugin :minitest
Hoe.plugin :gemspec # `gem install hoe-gemspec`
Hoe.plugin :git     # `gem install hoe-git`

Hoe.spec 'gda' do
  developer('Aaron Patterson', 'tenderlove@ruby-lang.org')
  self.readme_file   = 'README.rdoc'
  self.history_file  = 'CHANGELOG.rdoc'
  self.extra_rdoc_files  = FileList['*.rdoc']

  extra_dev_deps << ['rake-compiler', '>= 0.4.1']
  extra_dev_deps << ['sqlite3']

  self.spec_extras = {
    :extensions            => ["ext/gda/extconf.rb"],
    :required_ruby_version => '>= 1.9.3'
  }

  require "rake/extensiontask"

  Rake::ExtensionTask.new "gda", spec do |ext|
    ext.lib_dir = File.join(*['lib', ENV['FAT_DIR']].compact)
  end
end

task :test => :compile

# vim: syntax=ruby

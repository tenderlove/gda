require 'mkmf'

# :stopdoc:

ENV['PKG_CONFIG_PATH'] ||= '/usr/local/lib/pkgconfig'

dir_config 'libgda'

def asplode missing
  abort <<~MSG
    #{missing} is missing. Try 'brew install pkg-config libgda' if you are on OSX and have homebrew installed.
    You can also check https://github.com/GNOME/libgda for more info on how to install
    the dependency.
  MSG
end

available_libgda_pkg_config = nil
%w(5.0 6.0).each do |pkg_config_version|
  pkg_config "libgda-#{pkg_config_version}"
  available_libgda_pkg_config = find_header('libgda/sql-parser/gda-sql-parser.h')
  break if available_libgda_pkg_config
end

asplode("libgda") unless available_libgda_pkg_config
create_makefile 'gda'

# :startdoc:

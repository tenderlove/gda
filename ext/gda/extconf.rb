require 'mkmf'

# :stopdoc:

ENV['PKG_CONFIG_PATH'] ||= '/usr/local/Library/ENV/pkgconfig/10.8'

dir_config 'libgda'

def asplode missing
  abort "#{missing} is missing. Try 'brew install libgda'"
end

pkg_config 'libgda-5.0'
find_header('libgda/sql-parser/gda-sql-parser.h') || asplode("libgda")

create_makefile 'gda'


# :startdoc:

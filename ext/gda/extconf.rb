require 'mkmf'

# :stopdoc:

RbConfig::MAKEFILE_CONFIG['CC'] = ENV['CC'] if ENV['CC']

INCLUDEDIR = RbConfig::CONFIG['includedir']
LIBDIR     = RbConfig::CONFIG['libdir']
LIB_DIRS   = ['/opt/local/lib', '/usr/local/lib', LIBDIR, '/usr/lib']
libgda    = dir_config 'libgda', '/opt/local/include', '/opt/local/lib'

def asplode missing
  abort "#{missing} is missing. Try 'port install libgda +universal' " +
        "or 'yum install libgda-devel'"
end

pkg_config 'libgda-4.0'
find_header 'libgda/sql-parser/gda-sql-parser.h'

create_makefile 'gda'


# :startdoc:

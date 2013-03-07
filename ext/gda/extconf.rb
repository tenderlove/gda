require 'mkmf'

# :stopdoc:

ENV['PKG_CONFIG_PATH']= '/usr/local/Library/ENV/pkgconfig/mountain_lion'

dir_config 'libgda'

def asplode missing
  abort "#{missing} is missing. Try 'port install libgda +universal' " +
        "or 'yum install libgda-devel'"
end

pkg_config 'libgda-5.0'
find_header('libgda/sql-parser/gda-sql-parser.h') || asplode("rawr")

create_makefile 'gda'


# :startdoc:

#include <ruby.h>
#include <libgda/sql-parser/gda-sql-parser.h>

VALUE mGDA;

void Init_gda()
{
    VALUE mParser;

    mGDA = rb_define_module("GDA");
    mParser = rb_define_class_under(mGDA, "Parser", rb_cObject);
}

/* vim: set noet sws=4 sw=4: */

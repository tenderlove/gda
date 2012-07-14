#include <gda.h>

VALUE cStatement;

static VALUE serialize(VALUE self)
{
    GdaStatement * stmt;
    gchar * string;

    Data_Get_Struct(self, GdaStatement, stmt);

    string = gda_statement_serialize(stmt);
    return rb_str_new2(string);
}

void Init_gda_statement()
{
    cStatement = rb_define_class_under(mSQL, "Statement", rb_cObject);

    rb_define_method(cStatement, "serialize", serialize, 0);
}

/* vim: set noet sws=4 sw=4: */

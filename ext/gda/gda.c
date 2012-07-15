#include <gda.h>

VALUE mGDA;
VALUE mSQL;
VALUE cParser;

static VALUE allocate(VALUE klass)
{
    GdaSqlParser * parser;

    parser = gda_sql_parser_new();
    return Data_Wrap_Struct(klass, NULL, NULL, parser);
}

static VALUE parse(VALUE self, VALUE sql)
{
    GdaSqlParser * parser;
    GdaStatement * stmt;
    GError * error;
    const gchar * rest;

    Data_Get_Struct(self, GdaSqlParser, parser);

    stmt = gda_sql_parser_parse_string(parser, StringValuePtr(sql), &rest, &error);

    if (!stmt) {
	rb_raise(rb_eRuntimeError, "error parsing sql");
    }

    return Data_Wrap_Struct(cStatement, NULL, NULL, stmt);
}

void Init_gda()
{

    mGDA = rb_define_module("GDA");
    mSQL = rb_define_module_under(mGDA, "SQL");

    Init_gda_statement();
    Init_gda_nodes();
    cParser = rb_define_class_under(mSQL, "Parser", rb_cObject);

    rb_define_alloc_func(cParser, allocate);

    rb_define_method(cParser, "parse", parse, 1);

    gda_init();
}

/* vim: set noet sws=4 sw=4: */

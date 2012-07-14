#include <ruby.h>
#include <libgda/libgda.h>
#include <libgda/sql-parser/gda-sql-parser.h>

VALUE mGDA;
VALUE cStatement;

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

    return Data_Wrap_Struct(cStatement, NULL, NULL, stmt);
}

static VALUE serialize(VALUE self)
{
    GdaStatement * stmt;
    gchar * string;

    Data_Get_Struct(self, GdaStatement, stmt);

    string = gda_statement_serialize(stmt);
    return rb_str_new2(string);
}

void Init_gda()
{
    VALUE mSQL;
    VALUE cParser;

    gda_init();

    mGDA = rb_define_module("GDA");
    mSQL = rb_define_module_under(mGDA, "SQL");
    cParser = rb_define_class_under(mSQL, "Parser", rb_cObject);
    cStatement = rb_define_class_under(mSQL, "Statement", rb_cObject);

    rb_define_alloc_func(cParser, allocate);

    rb_define_method(cParser, "parse", parse, 1);

    rb_define_method(cStatement, "serialize", serialize, 0);
}

/* vim: set noet sws=4 sw=4: */

#include <gda.h>

VALUE cStatement;
VALUE cStructure;

static VALUE serialize(VALUE self)
{
    GdaStatement * stmt;
    gchar * string;

    Data_Get_Struct(self, GdaStatement, stmt);

    string = gda_statement_serialize(stmt);
    return rb_str_new2(string);
}

static VALUE ast(VALUE self)
{
    GdaSqlStatement * sqlst;

    Data_Get_Struct(self, GdaSqlStatement, sqlst);

    return WrapAnyPart(self, GDA_SQL_ANY_PART(sqlst->contents));
}

static VALUE sql(VALUE self)
{
    GdaSqlStatement * sqlst;

    Data_Get_Struct(self, GdaSqlStatement, sqlst);

    return rb_str_new2(sqlst->sql);
}

static VALUE structure(VALUE self)
{
    GdaStatement * stmt;
    GdaSqlStatement * sqlst;

    Data_Get_Struct(self, GdaStatement, stmt);

    g_object_get(G_OBJECT(stmt), "structure", &sqlst, NULL);

    return Data_Wrap_Struct(cStructure, NULL, gda_sql_statement_free, sqlst);
}

void Init_gda_statement()
{
    cStatement = rb_define_class_under(mSQL, "Statement", rb_cObject);
    cStructure = rb_define_class_under(mSQL, "Structure", rb_cObject);

    rb_define_method(cStatement, "serialize", serialize, 0);
    rb_define_method(cStatement, "structure", structure, 0);
    rb_define_method(cStructure, "ast", ast, 0);
    rb_define_method(cStructure, "sql", sql, 0);
}

/* vim: set noet sws=4 sw=4: */

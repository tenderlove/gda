#include <gda.h>

VALUE cStatement;
VALUE cStructure;

static void structure_free(void *data)
{
    gda_sql_statement_free((GdaSqlStatement *)data);
}

static size_t structure_memsize(const void *data)
{
    return sizeof(GdaSqlStatement);
}

static const rb_data_type_t structure_type = {
    "GDA::SQL::Structure",
    {
        NULL,
        structure_free,
        structure_memsize,
    },
    0,
    0,
    RUBY_TYPED_FREE_IMMEDIATELY | RUBY_TYPED_WB_PROTECTED,
};

static VALUE serialize(VALUE self)
{
    GdaStatement * stmt = gda_statement_unwrap(self);
    gchar * string;

    string = gda_statement_serialize(stmt);
    return rb_str_new2(string);
}

static VALUE ast(VALUE self)
{
    GdaSqlStatement * sqlst;
    TypedData_Get_Struct(self, GdaSqlStatement, &structure_type, sqlst);
    return WrapAnyPart(self, GDA_SQL_ANY_PART(sqlst->contents));
}

static VALUE sql(VALUE self)
{
    GdaSqlStatement * sqlst;
    TypedData_Get_Struct(self, GdaSqlStatement, &structure_type, sqlst);
    return rb_str_new2(sqlst->sql);
}

static VALUE structure(VALUE self)
{
    GdaStatement * stmt = gda_statement_unwrap(self);
    GdaSqlStatement * sqlst;

    g_object_get(G_OBJECT(stmt), "structure", &sqlst, NULL);

    return TypedData_Wrap_Struct(cStructure, &structure_type, sqlst);
}

void Init_gda_statement(void)
{
    rb_global_variable(&cStatement);
    cStatement = rb_define_class_under(mSQL, "Statement", rb_cObject);

    rb_global_variable(&cStructure);
    cStructure = rb_define_class_under(mSQL, "Structure", rb_cObject);

    rb_undef_alloc_func(cStatement);
    rb_undef_alloc_func(cStructure);

    rb_define_method(cStatement, "serialize", serialize, 0);
    rb_define_method(cStatement, "structure", structure, 0);
    rb_define_method(cStructure, "ast", ast, 0);
    rb_define_method(cStructure, "sql", sql, 0);
}

/* vim: set noet sws=4 sw=4: */

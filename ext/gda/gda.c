#include <gda.h>

VALUE mGDA;
VALUE mSQL;
VALUE cParser;

static void parser_free(void *data)
{
    g_object_unref((GdaSqlParser *)data);
}

static size_t parser_memsize(const void *data)
{
    return sizeof(GdaSqlParser);
}

static const rb_data_type_t parser_type = {
  "GDA::SQL::Parser",
  {
      NULL,
      parser_free,
      parser_memsize,
  },
  0,
  0,
  RUBY_TYPED_FREE_IMMEDIATELY | RUBY_TYPED_WB_PROTECTED,
};

VALUE gda_parser_wrap(VALUE klass, GdaSqlParser * parser)
{
    return TypedData_Wrap_Struct(klass, &parser_type, parser);
}

static VALUE allocate(VALUE klass)
{
    return gda_parser_wrap(klass, gda_sql_parser_new());
}

static void statement_free(void *data)
{
    g_object_unref((GdaStatement *)data);
}

static size_t statement_memsize(const void *data)
{
    return sizeof(GdaStatement);
}

static const rb_data_type_t statement_type = {
  "GDA::SQL::Statement",
  {
      NULL,
      statement_free,
      statement_memsize,
  },
  0,
  0,
  RUBY_TYPED_FREE_IMMEDIATELY | RUBY_TYPED_WB_PROTECTED,
};

GdaStatement *gda_statement_unwrap(VALUE self)
{
    GdaStatement * stmt;
    TypedData_Get_Struct(self, GdaStatement, &statement_type, stmt);
    return stmt;
}

static VALUE parse(VALUE self, VALUE sql)
{
    GdaSqlParser * parser;
    GdaStatement * stmt;
    GError * error = NULL;
    const gchar * rest;

    TypedData_Get_Struct(self, GdaSqlParser, &parser_type, parser);

    stmt = gda_sql_parser_parse_string(parser, StringValuePtr(sql), &rest, &error);

    if (!stmt) {
	rb_raise(rb_eRuntimeError, "error parsing sql");
    }

    return TypedData_Wrap_Struct(cStatement, &statement_type, stmt);
}

static VALUE providers(VALUE klass)
{
    GdaDataModel * providers;
    gint i, nb;
    VALUE list;

    list = rb_ary_new();
    providers = gda_config_list_providers();
    nb = gda_data_model_get_n_rows(providers);

    for (i = 0; i < nb; i++) {
	const gchar *pname;
	const GValue *cvalue;

	cvalue = gda_data_model_get_value_at(providers, 0, i, NULL);

	if (!cvalue)
	    rb_raise(rb_eRuntimeError, "can't load provider");

	pname = g_value_get_string(cvalue);

	rb_ary_push(list, rb_str_new2(pname));
    }

    g_object_unref(providers);

    return list;
}

static VALUE sql_identifier_split(VALUE klass, VALUE string)
{
    gchar ** list;
    int i;
    VALUE ids;

    ids = rb_ary_new();
    list = gda_sql_identifier_split(StringValuePtr(string));
    for (i = 0; list[i]; i++) {
	rb_ary_push(ids, rb_str_new2(list[i]));
    }
    g_strfreev(list);

    return ids;
}

void Init_gda(void)
{
    rb_global_variable(&mGDA);
    mGDA = rb_define_module("GDA");

    rb_global_variable(&mSQL);
    mSQL = rb_define_module_under(mGDA, "SQL");

    Init_gda_statement();
    Init_gda_nodes();
    Init_gda_provider();

    rb_global_variable(&cParser);
    cParser = rb_define_class_under(mSQL, "Parser", rb_cObject);

    rb_define_alloc_func(cParser, allocate);

    rb_define_method(cParser, "parse", parse, 1);

    rb_define_singleton_method(mSQL, "providers", providers, 0);
    rb_define_singleton_method(mGDA, "sql_identifier_split", sql_identifier_split, 1);

    gda_init();
}

/* vim: set noet sws=4 sw=4: */

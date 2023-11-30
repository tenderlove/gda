#include <gda.h>

VALUE cProvider;

static const rb_data_type_t provider_type = {
    "GDA::SQL::Provider",
    {
        NULL,
        NULL,
        NULL,
    },
    0,
    0,
    RUBY_TYPED_FREE_IMMEDIATELY | RUBY_TYPED_WB_PROTECTED,
};

static VALUE name(VALUE self)
{
    GdaServerProvider * pr;
    TypedData_Get_Struct(self, GdaServerProvider, &provider_type, pr);

    return rb_str_new2(gda_server_provider_get_name(pr));
}

static VALUE find(VALUE klass, VALUE string)
{
    GdaServerProvider * pr;
    GError * error = NULL;

    pr = gda_config_get_provider(StringValuePtr(string), &error);

    if (pr)
	return TypedData_Wrap_Struct(klass, &provider_type, pr);
    else {
	/* FIXME: should actually raise an error here. */
	g_error_free(error);
	return Qnil;
    }
}

static VALUE parser(VALUE self)
{
    GdaSqlParser * parser;
    GdaServerProvider * pr;

    TypedData_Get_Struct(self, GdaServerProvider, &provider_type, pr);

    parser = gda_server_provider_create_parser(pr, NULL);

    if (!parser)
	rb_raise(rb_eRuntimeError, "zomglol");

    return gda_parser_wrap(cParser, parser);
}

static VALUE quote_str(VALUE self, VALUE str)
{
    GdaServerProvider * pr;

    TypedData_Get_Struct(self, GdaServerProvider, &provider_type, pr);
    return rb_str_new2(gda_sql_identifier_quote(StringValuePtr(str), NULL, pr, TRUE, TRUE));
}

void Init_gda_provider()
{
    rb_global_variable(&cProvider);
    cProvider = rb_define_class_under(mSQL, "Provider", rb_cObject);

    rb_undef_alloc_func(cProvider);
    rb_define_singleton_method(cProvider, "find", find, 1);
    rb_define_method(cProvider, "name", name, 0);
    rb_define_method(cProvider, "parser", parser, 0);
    rb_define_method(cProvider, "quote", quote_str, 1);
}

/* vim: set noet sws=4 sw=4: */

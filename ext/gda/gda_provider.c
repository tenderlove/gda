#include <gda.h>

VALUE cProvider;

static VALUE find(VALUE klass, VALUE string)
{
    GdaServerProvider * pr;
    GError *error;

    pr = gda_config_get_provider(StringValuePtr(string), &error);

    if (pr)
	return Data_Wrap_Struct(klass, NULL, NULL, pr);
    else
	return Qnil;
}

void Init_gda_provider()
{
    cProvider = rb_define_class_under(mSQL, "Provider", rb_cObject);
    rb_define_singleton_method(cProvider, "find", find, 1);
}

/* vim: set noet sws=4 sw=4: */

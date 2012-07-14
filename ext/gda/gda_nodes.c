#include <gda.h>

VALUE mNodes;
VALUE cSelect;
VALUE cFrom;
VALUE cSelectField;

static VALUE from(VALUE self)
{
    GdaSqlStatementSelect *st;

    Data_Get_Struct(self, GdaSqlStatementSelect, st);

    return WrapAnyPart((GdaSqlAnyPart *)st->from);
}

static VALUE distinct_expr(VALUE self)
{
    GdaSqlStatementSelect *st;

    Data_Get_Struct(self, GdaSqlStatementSelect, st);

    return WrapAnyPart((GdaSqlAnyPart *)st->distinct_expr);
}

static VALUE expr_list(VALUE self)
{
    GdaSqlStatementSelect *st;
    GSList *list;
    VALUE rb_list;

    Data_Get_Struct(self, GdaSqlStatementSelect, st);

    rb_list = rb_ary_new();
    list = st->expr_list;

    while(list) {
	rb_ary_push(rb_list, WrapAnyPart((GdaSqlAnyPart *)list->data));
	list = list->next;
    }

    return rb_list;
}

VALUE WrapAnyPart(GdaSqlAnyPart *part)
{
    if (!part)
	return Qnil;

    switch(part->type) {
	case GDA_SQL_ANY_STMT_SELECT:
	    return Data_Wrap_Struct(cSelect, NULL, NULL, part);
	    break;
	case GDA_SQL_ANY_SQL_SELECT_FROM:
	    return Data_Wrap_Struct(cFrom, NULL, NULL, part);
	    break;
	case GDA_SQL_ANY_SQL_SELECT_FIELD:
	    return Data_Wrap_Struct(cSelectField, NULL, NULL, part);
	    break;
	default:
	    printf("unknown part: %d\n", part->type);
	    return Qnil;
    }
}

void Init_gda_nodes()
{
    mNodes = rb_define_module_under(mGDA, "Nodes");

    cSelect = rb_define_class_under(mNodes, "Select", rb_cObject);
    cFrom = rb_define_class_under(mNodes, "From", rb_cObject);
    cSelectField = rb_define_class_under(mNodes, "SelectField", rb_cObject);

    rb_define_method(cSelect, "from", from, 0);
    rb_define_method(cSelect, "distinct_expr", distinct_expr, 0);
    rb_define_method(cSelect, "expr_list", expr_list, 0);
}

/* vim: set noet sws=4 sw=4: */

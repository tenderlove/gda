#include <gda.h>

VALUE mNodes;
VALUE cSelect;
VALUE cFrom;
VALUE cSelectField;
VALUE cExpr;
VALUE cOrder;

#define WrapNode(type, lname) \
    static VALUE lname(VALUE self) \
{ \
    type *st;\
    Data_Get_Struct(self, type, st); \
    return WrapAnyPart((GdaSqlAnyPart *)st->lname); \
}

#define WrapList(type, lname) \
    static VALUE lname(VALUE self) \
{ \
    type *ptr; \
    GSList *list; \
    VALUE rb_list; \
    Data_Get_Struct(self, type, ptr);\
    rb_list = rb_ary_new(); \
    list = ptr->lname; \
    while(list) { \
	rb_ary_push(rb_list, WrapAnyPart((GdaSqlAnyPart *)list->data)); \
	list = list->next; \
    } \
    return rb_list; \
}

WrapNode(GdaSqlStatementSelect, distinct_expr);
WrapList(GdaSqlStatementSelect, expr_list);
WrapNode(GdaSqlStatementSelect, from);
WrapNode(GdaSqlStatementSelect, where_cond);
WrapList(GdaSqlStatementSelect, group_by);
WrapNode(GdaSqlStatementSelect, having_cond);
WrapList(GdaSqlStatementSelect, order_by);
WrapNode(GdaSqlStatementSelect, limit_count);
WrapNode(GdaSqlStatementSelect, limit_offset);

static VALUE distinct_p(VALUE self)
{
    GdaSqlStatementSelect * st;

    Data_Get_Struct(self, GdaSqlStatementSelect, st);

    if (st->distinct)
	return Qtrue;

    return Qfalse;
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
	case GDA_SQL_ANY_EXPR:
	    return Data_Wrap_Struct(cExpr, NULL, NULL, part);
	    break;
	case GDA_SQL_ANY_SQL_SELECT_ORDER:
	    return Data_Wrap_Struct(cOrder, NULL, NULL, part);
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
    cExpr = rb_define_class_under(mNodes, "Expr", rb_cObject);
    cOrder = rb_define_class_under(mNodes, "Order", rb_cObject);

    rb_define_method(cSelect, "from", from, 0);
    rb_define_method(cSelect, "distinct_expr", distinct_expr, 0);
    rb_define_method(cSelect, "expr_list", expr_list, 0);
    rb_define_method(cSelect, "where_cond", where_cond, 0);
    rb_define_method(cSelect, "group_by", group_by, 0);
    rb_define_method(cSelect, "having_cond", having_cond, 0);
    rb_define_method(cSelect, "order_by", order_by, 0);
    rb_define_method(cSelect, "limit_count", limit_count, 0);
    rb_define_method(cSelect, "limit_offset", limit_offset, 0);
    rb_define_method(cSelect, "distinct?", distinct_p, 0);
}

/* vim: set noet sws=4 sw=4: */

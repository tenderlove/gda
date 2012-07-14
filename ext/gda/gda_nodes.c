#include <gda.h>

VALUE mNodes;
VALUE cSelect;
VALUE cFrom;
VALUE cSelectField;
VALUE cExpr;
VALUE cOrder;
VALUE cNode;
VALUE cOperation;
VALUE cTarget;

#define WrapNode(type, lname) \
    static VALUE rb_gda_##lname(VALUE self) \
{ \
    type *st;\
    Data_Get_Struct(self, type, st); \
    return WrapAnyPart((GdaSqlAnyPart *)st->lname); \
}

#define WrapList(type, lname) \
    static VALUE rb_gda_##lname(VALUE self) \
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

WrapNode(GdaSqlSelectField, expr);

WrapNode(GdaSqlExpr, func);
WrapNode(GdaSqlExpr, cond);
WrapNode(GdaSqlExpr, select);
WrapNode(GdaSqlExpr, case_s);
WrapNode(GdaSqlExpr, param_spec);

WrapList(GdaSqlSelectFrom, targets);
WrapList(GdaSqlSelectFrom, joins);

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
	case GDA_SQL_ANY_SQL_OPERATION:
	    return Data_Wrap_Struct(cOperation, NULL, NULL, part);
	    break;
	case GDA_SQL_ANY_SQL_SELECT_TARGET:
	    return Data_Wrap_Struct(cTarget, NULL, NULL, part);
	    break;
	default:
	    printf("unknown part: %d\n", part->type);
	    return Qnil;
    }
}

void Init_gda_nodes()
{
    mNodes = rb_define_module_under(mGDA, "Nodes");

    cNode = rb_define_class_under(mNodes, "Node", rb_cObject);

    cOrder = rb_define_class_under(mNodes, "Order", cNode);

    cSelect = rb_define_class_under(mNodes, "Select", cNode);
    rb_define_method(cSelect, "from", rb_gda_from, 0);
    rb_define_method(cSelect, "distinct_expr", rb_gda_distinct_expr, 0);
    rb_define_method(cSelect, "expr_list", rb_gda_expr_list, 0);
    rb_define_method(cSelect, "where_cond", rb_gda_where_cond, 0);
    rb_define_method(cSelect, "group_by", rb_gda_group_by, 0);
    rb_define_method(cSelect, "having_cond", rb_gda_having_cond, 0);
    rb_define_method(cSelect, "order_by", rb_gda_order_by, 0);
    rb_define_method(cSelect, "limit_count", rb_gda_limit_count, 0);
    rb_define_method(cSelect, "limit_offset", rb_gda_limit_offset, 0);
    rb_define_method(cSelect, "distinct?", distinct_p, 0);

    cSelectField = rb_define_class_under(mNodes, "SelectField", cNode);
    rb_define_method(cSelectField, "expr", rb_gda_expr, 0);

    cExpr = rb_define_class_under(mNodes, "Expr", cNode);
    rb_define_method(cExpr, "func", rb_gda_func, 0);
    rb_define_method(cExpr, "cond", rb_gda_cond, 0);
    rb_define_method(cExpr, "select", rb_gda_select, 0);
    rb_define_method(cExpr, "case_s", rb_gda_case_s, 0);
    rb_define_method(cExpr, "param_spec", rb_gda_param_spec, 0);

    cFrom = rb_define_class_under(mNodes, "From", cNode);
    rb_define_method(cFrom, "targets", rb_gda_targets, 0);
    rb_define_method(cFrom, "joins", rb_gda_joins, 0);

    cOperation = rb_define_class_under(mNodes, "Operation", cNode);
    cTarget = rb_define_class_under(mNodes, "Target", cNode);
}

/* vim: set noet sws=4 sw=4: */

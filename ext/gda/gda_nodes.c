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

#define WrapNode(klass, type, lname) \
    static VALUE rb_##klass##_##lname(VALUE self) \
{ \
    type *st;\
    Data_Get_Struct(self, type, st); \
    return WrapAnyPart((GdaSqlAnyPart *)st->lname); \
}

#define WrapList(klass, type, lname) \
    static VALUE rb_##klass##_##lname(VALUE self) \
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

#define WrapperMethod(klass, lname) \
    rb_define_method(klass, #lname, rb_##klass##_##lname, 0);

WrapNode(cSelect, GdaSqlStatementSelect, distinct_expr);
WrapList(cSelect, GdaSqlStatementSelect, expr_list);
WrapNode(cSelect, GdaSqlStatementSelect, from);
WrapNode(cSelect, GdaSqlStatementSelect, where_cond);
WrapList(cSelect, GdaSqlStatementSelect, group_by);
WrapNode(cSelect, GdaSqlStatementSelect, having_cond);
WrapList(cSelect, GdaSqlStatementSelect, order_by);
WrapNode(cSelect, GdaSqlStatementSelect, limit_count);
WrapNode(cSelect, GdaSqlStatementSelect, limit_offset);

WrapNode(cSelectField, GdaSqlSelectField, expr);

WrapNode(cExpr, GdaSqlExpr, func);
WrapNode(cExpr, GdaSqlExpr, cond);
WrapNode(cExpr, GdaSqlExpr, select);
WrapNode(cExpr, GdaSqlExpr, case_s);
WrapNode(cExpr, GdaSqlExpr, param_spec);

WrapList(cFrom, GdaSqlSelectFrom, targets);
WrapList(cFrom, GdaSqlSelectFrom, joins);

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
    rb_define_method(cSelect, "distinct?", distinct_p, 0);

    WrapperMethod(cSelect, from);
    WrapperMethod(cSelect, distinct_expr);
    WrapperMethod(cSelect, expr_list);
    WrapperMethod(cSelect, where_cond);
    WrapperMethod(cSelect, group_by);
    WrapperMethod(cSelect, having_cond);
    WrapperMethod(cSelect, order_by);
    WrapperMethod(cSelect, limit_count);
    WrapperMethod(cSelect, limit_offset);

    cSelectField = rb_define_class_under(mNodes, "SelectField", cNode);
    WrapperMethod(cSelectField, expr);

    cExpr = rb_define_class_under(mNodes, "Expr", cNode);
    WrapperMethod(cExpr, func);
    WrapperMethod(cExpr, cond);
    WrapperMethod(cExpr, select);
    WrapperMethod(cExpr, case_s);
    WrapperMethod(cExpr, param_spec);

    cFrom = rb_define_class_under(mNodes, "From", cNode);
    WrapperMethod(cFrom, targets);
    WrapperMethod(cFrom, joins);

    cOperation = rb_define_class_under(mNodes, "Operation", cNode);
    cTarget = rb_define_class_under(mNodes, "Target", cNode);
}

/* vim: set noet sws=4 sw=4: */

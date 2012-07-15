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
VALUE cFunction;
VALUE cInsert;
VALUE cDelete;
VALUE cUpdate;
VALUE cTable;
VALUE cUnknown;

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

WrapList(cOperation, GdaSqlOperation, operands);

WrapNode(cTarget, GdaSqlSelectTarget, expr);

WrapList(cFunction, GdaSqlFunction, args_list);

WrapNode(cOrder, GdaSqlSelectOrder, expr);

WrapNode(cInsert, GdaSqlStatementInsert, table);
WrapList(cInsert, GdaSqlStatementInsert, fields_list);
WrapList(cInsert, GdaSqlStatementInsert, values_list);
WrapNode(cInsert, GdaSqlStatementInsert, select);

WrapNode(cUpdate, GdaSqlStatementUpdate, table);
WrapList(cUpdate, GdaSqlStatementUpdate, fields_list);
WrapList(cUpdate, GdaSqlStatementUpdate, expr_list);
WrapNode(cUpdate, GdaSqlStatementUpdate, cond);

WrapNode(cDelete, GdaSqlStatementDelete, table);
WrapNode(cDelete, GdaSqlStatementDelete, cond);

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
	case GDA_SQL_ANY_STMT_INSERT:
	    return Data_Wrap_Struct(cInsert, NULL, NULL, part);
	    break;
	case GDA_SQL_ANY_STMT_UPDATE:
	    return Data_Wrap_Struct(cUpdate, NULL, NULL, part);
	    break;
	case GDA_SQL_ANY_STMT_DELETE:
	    return Data_Wrap_Struct(cDelete, NULL, NULL, part);
	    break;
	case GDA_SQL_ANY_STMT_UNKNOWN:
	    return Data_Wrap_Struct(cUnknown, NULL, NULL, part);
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
	case GDA_SQL_ANY_SQL_TABLE:
	    return Data_Wrap_Struct(cTable, NULL, NULL, part);
	    break;
	case GDA_SQL_ANY_SQL_OPERATION:
	    return Data_Wrap_Struct(cOperation, NULL, NULL, part);
	    break;
	case GDA_SQL_ANY_SQL_FUNCTION:
	    return Data_Wrap_Struct(cFunction, NULL, NULL, part);
	    break;
	case GDA_SQL_ANY_SQL_SELECT_TARGET:
	    return Data_Wrap_Struct(cTarget, NULL, NULL, part);
	    break;
	default:
	    rb_raise(rb_eRuntimeError, "unknown node type: %d\n", part->type);
	    return Qnil;
    }
}

void Init_gda_nodes()
{
    mNodes = rb_define_module_under(mGDA, "Nodes");

    cNode = rb_define_class_under(mNodes, "Node", rb_cObject);

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
    WrapperMethod(cOperation, operands);

    cTarget = rb_define_class_under(mNodes, "Target", cNode);
    WrapperMethod(cTarget, expr);

    cFunction = rb_define_class_under(mNodes, "Function", cNode);
    WrapperMethod(cFunction, args_list);

    cOrder = rb_define_class_under(mNodes, "Order", cNode);
    WrapperMethod(cOrder, expr);

    cInsert = rb_define_class_under(mNodes, "Insert", cNode);
    WrapperMethod(cInsert, table);
    WrapperMethod(cInsert, fields_list);
    WrapperMethod(cInsert, values_list);
    WrapperMethod(cInsert, select);

    cDelete = rb_define_class_under(mNodes, "Delete", cNode);
    WrapperMethod(cDelete, table);
    WrapperMethod(cDelete, cond);

    cUpdate = rb_define_class_under(mNodes, "Update", cNode);
    WrapperMethod(cUpdate, table);
    WrapperMethod(cUpdate, fields_list);
    WrapperMethod(cUpdate, expr_list);
    WrapperMethod(cUpdate, cond);

    cTable = rb_define_class_under(mNodes, "Table", cNode);

    cUnknown = rb_define_class_under(mNodes, "Unknown", cNode);
}

/* vim: set noet sws=4 sw=4: */

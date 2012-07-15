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
VALUE cJoin;
VALUE cField;
VALUE cRollbackSavepoint;
VALUE cDeleteSavepoint;
VALUE cSavepoint;
VALUE cBegin;
VALUE cRollback;
VALUE cCommit;

#define WrapString(klass, type, lname) \
    static VALUE rb_##klass##_##lname(VALUE self) \
{ \
    type *st;\
    Data_Get_Struct(self, type, st); \
    if (st->lname) \
      return rb_str_new2(st->lname); \
    else \
      return Qnil; \
}

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

WrapString(cTable, GdaSqlTable, table_name);

WrapString(cField, GdaSqlField, field_name);

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
WrapString(cSelectField, GdaSqlSelectField, field_name);
WrapString(cSelectField, GdaSqlSelectField, table_name);
WrapString(cSelectField, GdaSqlSelectField, as);

WrapNode(cExpr, GdaSqlExpr, func);
WrapNode(cExpr, GdaSqlExpr, cond);
WrapNode(cExpr, GdaSqlExpr, select);
WrapNode(cExpr, GdaSqlExpr, case_s);
WrapNode(cExpr, GdaSqlExpr, param_spec);
WrapString(cExpr, GdaSqlExpr, value);
WrapString(cExpr, GdaSqlExpr, cast_as);

WrapList(cFrom, GdaSqlSelectFrom, targets);
WrapList(cFrom, GdaSqlSelectFrom, joins);

WrapList(cOperation, GdaSqlOperation, operands);

WrapNode(cTarget, GdaSqlSelectTarget, expr);
WrapString(cTarget, GdaSqlSelectTarget, table_name);
WrapString(cTarget, GdaSqlSelectTarget, as);

WrapList(cFunction, GdaSqlFunction, args_list);
WrapString(cFunction, GdaSqlFunction, function_name);

WrapNode(cOrder, GdaSqlSelectOrder, expr);

WrapNode(cInsert, GdaSqlStatementInsert, table);
WrapList(cInsert, GdaSqlStatementInsert, fields_list);
WrapNode(cInsert, GdaSqlStatementInsert, select);
WrapString(cInsert, GdaSqlStatementInsert, on_conflict);

WrapNode(cUpdate, GdaSqlStatementUpdate, table);
WrapList(cUpdate, GdaSqlStatementUpdate, fields_list);
WrapList(cUpdate, GdaSqlStatementUpdate, expr_list);
WrapNode(cUpdate, GdaSqlStatementUpdate, cond);

WrapNode(cDelete, GdaSqlStatementDelete, table);
WrapNode(cDelete, GdaSqlStatementDelete, cond);

WrapNode(cJoin, GdaSqlSelectJoin, expr);
WrapList(cJoin, GdaSqlSelectJoin, use);

WrapList(cUnknown, GdaSqlStatementUnknown, expressions);

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
	case GDA_SQL_ANY_STMT_BEGIN:
	    return Data_Wrap_Struct(cBegin, NULL, NULL, part);
	    break;
	case GDA_SQL_ANY_STMT_ROLLBACK:
	    return Data_Wrap_Struct(cRollback, NULL, NULL, part);
	    break;
	case GDA_SQL_ANY_STMT_COMMIT:
	    return Data_Wrap_Struct(cCommit, NULL, NULL, part);
	    break;
	case GDA_SQL_ANY_STMT_SAVEPOINT:
	    return Data_Wrap_Struct(cSavepoint, NULL, NULL, part);
	    break;
	case GDA_SQL_ANY_STMT_ROLLBACK_SAVEPOINT:
	    return Data_Wrap_Struct(cRollbackSavepoint, NULL, NULL, part);
	    break;
	case GDA_SQL_ANY_STMT_DELETE_SAVEPOINT:
	    return Data_Wrap_Struct(cDeleteSavepoint, NULL, NULL, part);
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
	case GDA_SQL_ANY_SQL_FIELD:
	    return Data_Wrap_Struct(cField, NULL, NULL, part);
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
	case GDA_SQL_ANY_SQL_SELECT_JOIN:
	    return Data_Wrap_Struct(cJoin, NULL, NULL, part);
	    break;
	default:
	    rb_raise(rb_eRuntimeError, "unknown node type: %d\n", part->type);
	    return Qnil;
    }
}

static VALUE rb_cInsert_values_list(VALUE self)
{
    GdaSqlStatementInsert * st;
    GSList * list;
    VALUE array;

    Data_Get_Struct(self, GdaSqlStatementInsert, st);

    array = rb_ary_new();
    list = st->values_list;
    while(list) {
	VALUE iarray = rb_ary_new();
	GSList * inner = (GSList *)list->data;

	while(inner) {
	  rb_ary_push(iarray, WrapAnyPart((GdaSqlAnyPart *)inner->data));
	  inner = inner->next;
	}

	rb_ary_push(array, iarray);
	list = list->next;
    }

    return array;
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
    WrapperMethod(cSelectField, field_name);
    WrapperMethod(cSelectField, table_name);
    WrapperMethod(cSelectField, as);

    cExpr = rb_define_class_under(mNodes, "Expr", cNode);
    WrapperMethod(cExpr, func);
    WrapperMethod(cExpr, cond);
    WrapperMethod(cExpr, select);
    WrapperMethod(cExpr, case_s);
    WrapperMethod(cExpr, param_spec);
    WrapperMethod(cExpr, value);
    WrapperMethod(cExpr, cast_as);

    cFrom = rb_define_class_under(mNodes, "From", cNode);
    WrapperMethod(cFrom, targets);
    WrapperMethod(cFrom, joins);

    cOperation = rb_define_class_under(mNodes, "Operation", cNode);
    WrapperMethod(cOperation, operands);

    cTarget = rb_define_class_under(mNodes, "Target", cNode);
    WrapperMethod(cTarget, expr);
    WrapperMethod(cTarget, table_name);
    WrapperMethod(cTarget, as);

    cFunction = rb_define_class_under(mNodes, "Function", cNode);
    WrapperMethod(cFunction, args_list);
    WrapperMethod(cFunction, function_name);

    cOrder = rb_define_class_under(mNodes, "Order", cNode);
    WrapperMethod(cOrder, expr);

    cInsert = rb_define_class_under(mNodes, "Insert", cNode);
    WrapperMethod(cInsert, table);
    WrapperMethod(cInsert, values_list);
    WrapperMethod(cInsert, fields_list);
    WrapperMethod(cInsert, select);
    WrapperMethod(cInsert, on_conflict);

    cDelete = rb_define_class_under(mNodes, "Delete", cNode);
    WrapperMethod(cDelete, table);
    WrapperMethod(cDelete, cond);

    cUpdate = rb_define_class_under(mNodes, "Update", cNode);
    WrapperMethod(cUpdate, table);
    WrapperMethod(cUpdate, fields_list);
    WrapperMethod(cUpdate, expr_list);
    WrapperMethod(cUpdate, cond);

    cTable = rb_define_class_under(mNodes, "Table", cNode);
    WrapperMethod(cTable, table_name);

    cUnknown = rb_define_class_under(mNodes, "Unknown", cNode);
    WrapperMethod(cUnknown, expressions);

    cJoin = rb_define_class_under(mNodes, "Join", cNode);
    WrapperMethod(cJoin, expr);
    WrapperMethod(cJoin, use);

    cField = rb_define_class_under(mNodes, "Field", cNode);
    WrapperMethod(cField, field_name);

    cBegin = rb_define_class_under(mNodes, "Begin", cNode);
    cRollback = rb_define_class_under(mNodes, "Rollback", cNode);
    cCommit = rb_define_class_under(mNodes, "Commit", cNode);
    cSavepoint = rb_define_class_under(mNodes, "Savepoint", cNode);
    cRollbackSavepoint = rb_define_class_under(mNodes, "RollbackSavepoint", cNode);
    cDeleteSavepoint = rb_define_class_under(mNodes, "DeleteSavepoint", cNode);
}

/* vim: set noet sws=4 sw=4: */

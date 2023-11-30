#ifndef _RUBY_GDA_NODES
#define _RUBY_GDA_NODES

void Init_gda_nodes(void);

VALUE WrapAnyPart(VALUE stmt, GdaSqlAnyPart *part);

#endif


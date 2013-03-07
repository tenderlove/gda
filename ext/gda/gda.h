#ifndef _RUBY_GDA
#define _RUBY_GDA

#include <ruby.h>
#include <libgda/libgda.h>
#include <libgda/sql-parser/gda-sql-parser.h>
#include <libgda/sql-parser/gda-sql-statement.h>

extern VALUE mGDA;
extern VALUE mSQL;
extern VALUE cStatement;
extern VALUE cParser;

#include <gda_statement.h>
#include <gda_nodes.h>
#include <gda_provider.h>

#endif

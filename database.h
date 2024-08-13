#ifndef DATABASE_H
#define DATABASE_H

#include "sqlite3.h"

int execute_query(sqlite3 *db, const char *sql);
int execute_schema(sqlite3 *db, const char *schema_file);

#endif

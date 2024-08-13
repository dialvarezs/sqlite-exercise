#include <stdio.h>
#include "sqlite3.h"
#include "database.h"

const char *DATABASE_NAME = "test.db";

int main()
{
    sqlite3 *db;
    int rc = sqlite3_open(DATABASE_NAME, &db);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    rc = execute_schema(db, "schema.sql");
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to execute schema: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char *sql_insert = "INSERT INTO Users (name) VALUES ('Juan Pérez' 'jp@test.com')";
    rc = execute_query(db, sql_insert);

    char *sql_query = "SELECT * FROM user";
    rc = execute_query(db, sql_query);

    sqlite3_close(db);
    return 0;
}

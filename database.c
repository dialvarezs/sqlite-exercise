#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "database.h"

int execute_query(sqlite3 *db, const char *sql)
{
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        num_cols = sqlite3_column_count(stmt);
        for (int i = 0; i < num_cols; i++)
        {
            printf("%s = %s\n", sqlite3_column_name(stmt, i), sqlite3_column_text(stmt, i));
        }
    }

    if (rc != SQLITE_DONE)
    {
        fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return rc;
    }

    sqlite3_finalize(stmt);
    return SQLITE_OK;
}

int execute_schema(sqlite3 *db, const char *schema_file)
{
    FILE *file = fopen(schema_file, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Cannot open schema file: %s\n", schema_file);
        return SQLITE_ERROR;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *sql = (char *)malloc(file_size + 1);
    if (sql == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return SQLITE_ERROR;
    }

    fread(sql, 1, file_size, file);
    sql[file_size] = '\0';

    fclose(file);

    int rc = sqlite3_exec(db, sql, 0, 0, NULL);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to execute schema: %s\n", sqlite3_errmsg(db));
    }

    free(sql);
    return rc == SQLITE_DONE ? SQLITE_OK : rc;
}

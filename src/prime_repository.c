#include <stdlib.h>
#include "prime_repository.h"
#include "sqlite3.h"
#include "def.h"
#include "stdio.h"
#include "string.h"
#include "spu_alarm.h"


sqlite3 *open_db() {
    sqlite3 *db;
    int rc = sqlite3_open(DB_NAME, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Unable to open db %s: %s", DB_NAME, sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }
    return db;
}

sqlite3_stmt *create_statement(sqlite3 *db, const char *sql) {
    sqlite3_stmt *stmt = NULL;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Unable to create statement: %s! Message: %s", sql, sqlite3_errmsg(db));
        sqlite3_close(db);
        sqlite3_finalize(stmt);
        exit(EXIT_FAILURE);
    }
    return stmt;
}

void prime_update(int id,char *name, int value) {
    const char *sql;
    sqlite3 *db = open_db();
    sql = "INSERT INTO server_data(ID,NAME,VALUE) VALUES (?,?,?) "
          "ON CONFLICT(ID) DO UPDATE SET "
          "VALUE=excluded.VALUE,"
          "NAME=excluded.NAME ";
    sqlite3_stmt *stmt = create_statement(db,sql);
    sqlite3_bind_int64(stmt, 1, id);
    sqlite3_bind_text(stmt, 2, name, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int64(stmt, 3, value);
    if(sqlite3_step(stmt)!=SQLITE_DONE){
        fprintf(stderr,"Error updating row! %s", sqlite3_errmsg(db));
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void prime_insert(char *name, int value) {
    sqlite3 *db = open_db();
    sqlite3_stmt *stmt = create_statement(db,"INSERT INTO server_data(NAME,VALUE) VALUES (?,?)");
    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int64(stmt, 2, value);
    if(sqlite3_step(stmt)!=SQLITE_DONE){
        fprintf(stderr,"Error inserting row! %s", sqlite3_errmsg(db));
    }
    Alarm(PRINT,"++++++++++ INSERTED KEY:VALUE [%s,%d] ++++++++++\n", name,value);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void prime_delete(char *name) {
    sqlite3 *db = open_db();
    sqlite3_stmt *stmt = create_statement(db,"DELETE FROM server_data WHERE NAME=?");
    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_TRANSIENT);
    if(sqlite3_step(stmt)!=SQLITE_DONE){
        fprintf(stderr,"Error deleting row! %s", sqlite3_errmsg(db));
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
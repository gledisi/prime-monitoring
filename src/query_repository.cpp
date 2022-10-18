//
// Created by gledisgjinaj on 10/10/22.
//

#include "query_repository.h"
#include "string"
#include "iostream"
#include "memory"
#include "sqlite3.h"
#include "def.h"

using database = unique_ptr<sqlite3,decltype(&sqlite3_close)>;
using statement = unique_ptr<sqlite3_stmt, decltype(&sqlite3_finalize)>;

database open_db(){
    sqlite3 *db;
    auto rc = sqlite3_open(DB_NAME,&db);
    if(rc!=SQLITE_OK){
        cerr << "Unable to open db:" << DB_NAME << sqlite3_errmsg(db);
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }
    return database{db,sqlite3_close};
}

statement create_statement(sqlite3* db,const string& sql){
    sqlite3_stmt* stmt = nullptr;
    int rc = sqlite3_prepare_v2(db,sql.c_str(),sql.length(),&stmt, nullptr);
    if(rc !=SQLITE_OK){
        cerr << "Unable to create statement:" << sqlite3_errmsg(db);
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }
    return statement{stmt, sqlite3_finalize};
}

void parameter(sqlite3_stmt* stmt,int index,int64_t value){
    if(sqlite3_bind_int64(stmt,index,value)!= SQLITE_OK){
        throw "Couldn't bind parameter";
    }
}

void parameter(sqlite3_stmt* stmt,int index,const string& value){
    if(sqlite3_bind_text(stmt,index,value.c_str(),value.size(),SQLITE_TRANSIENT)!= SQLITE_OK){
        throw "Couldn't bind parameter";
    }
}

ostringstream query_repository::get_by_key(string name){
    auto db = open_db();
    auto stmt = create_statement(db.get(),"SELECT * from server_data WHERE NAME = ?");
    parameter(stmt.get(),1,name);
    ostringstream  os = read_server_data_row(stmt.get());
    sqlite3_close(db.get());
    return os;
}

ostringstream query_repository::get_all(){
    auto db = open_db();
    auto stmt = create_statement(db.get(),"SELECT * from server_data");
    ostringstream  os = read_server_data_row(stmt.get());
    sqlite3_close(db.get());
    return os;
}

ostringstream query_repository::read_server_data_row(sqlite3_stmt* stmt){
    ostringstream buffer;
    buffer << "[ \n";
    while (sqlite3_step(stmt)==SQLITE_ROW) {
        buffer <<"{ \n";
        const unsigned char *r2 = sqlite3_column_text(stmt, 1);
        std::string name_res(reinterpret_cast< char const * >(r2));
        buffer <<"id: " << sqlite3_column_int(stmt, 0) << "\n";
        buffer <<"name: "<< name_res << "\n";
        buffer <<"value: " << sqlite3_column_int(stmt, 2) << "\n";
        buffer <<"} \n";
    }
    buffer << "] \n";
    return buffer;
}
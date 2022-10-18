//
// Created by gledisgjinaj on 10/10/22.
//

#ifndef SRC_QUERY_REPOSITORY_H
#define SRC_QUERY_REPOSITORY_H

#include "sstream"
#include "sqlite3.h"

using namespace std;

class query_repository {

public:
        ostringstream get_by_key(string name);
        ostringstream get_all();

private:
        static ostringstream read_server_data_row(sqlite3_stmt *stmt);
};

#endif //SRC_QUERY_REPOSITORY_H

#include "rest_api.h"
#include "crow.h"
#include "query_repository.h"

extern "C" {
#include "client.h"
}

rest_api::rest_api(char* port) {
    crow::SimpleApp  app;

    CROW_ROUTE(app, "/query")([](){
        query_repository repo;
        return crow::response(repo.get_all().str());
    });

    CROW_ROUTE(app, "/query/<string>")([](string n){
        query_repository rep;
        return crow::response(rep.get_by_key(n).str());
    });

    CROW_ROUTE(app, "/update/<string>/<int>")([](std::string key,int val){
        Send_Update(key.c_str(),val);
        return "OK";
    });

    CROW_ROUTE(app, "/insert/<string>/<int>")([](std::string key,int val){
        Send_Update(key.c_str(),val);
        //usleep(100);
        return "OK";
    });

    std::string str(port);
    app.port(stoi(str)).multithreaded().run();
}
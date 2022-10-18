#include <iostream>
#include <thread>
#include <algorithm>
#include "rest_api.h"
extern "C" {
#include "client.h"
}

char* getCmdOption(char ** begin, char ** end, const std::string & option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end){
        return *itr;
    }
    return 0;
}

void start_api(char* port){
    std::cout << "Starting api in port: "<< port;
    rest_api restApi(port);
}

int main(int argc, char** argv){
    char* port = getCmdOption(argv, argv + argc, "-p");
    std::thread t(&start_api,port);
    std::cout << "main thread\n";
    init_client(argc, argv);
    t.detach();
    return 0;
}

#include <iostream>
#include <bits/stdc++.h>
#include "include/db.hpp"
#include "include/listener.hpp"
#include "include/network_utils.hpp"

using namespace web;
using namespace cfx;

int main(int argc, char** argv)
{
    sqlite3* db = nullptr;
    if (sqlite3_open(argv[1], &db) != SQLITE_OK)
    {
        std::cerr << "Failed to open database: " << sqlite3_errmsg(db) << std::endl;
        return EXIT_FAILURE;
    }
    if (!createProfileTable(db) || !createReviewTable(db))
    {
        return EXIT_FAILURE;
    }
    
    Listener server(db);
    server.setEndpoint(argv[2]);
    
    try {
        server.accept().wait();
        std::cout << "Modern C++ Microservice now listening for requests at: " << server.endpoint() << '\n';
        while(1);
        // server.shutdown().wait();
    }
    catch(std::exception & e) {
        std::cerr << "something wrong happened! :(" << '\n';
    }

    sqlite3_close(db);

    return EXIT_SUCCESS;
}
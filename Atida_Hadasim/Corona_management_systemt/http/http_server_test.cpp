#include <iostream>

#include "http_server.hpp"

int main() 
{
    HttpServer server("http://localhost:8080");
    server.run();

    return 0;
}
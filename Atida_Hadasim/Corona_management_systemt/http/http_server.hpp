#include <cpprest/http_listener.h>
#include <cpprest/json.h>

#include "user_management.hpp"

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

class HttpServer 
{
public:
    HttpServer(utility::string_t url);
    void run();

private:

    void handle_get(http_request request);
    void handle_post(http_request request); 
    void handle_put(http_request request); 
    void handle_delete(http_request request); 

    http_listener m_listener;
    userManagement m_manage_db;
};
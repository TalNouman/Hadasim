// Add necessary headers for HTTP server and JSON parsing
#include <cpprest/http_listener.h>
#include <cpprest/json.h>

#include "http_server.hpp"

HttpServer::HttpServer(utility::string_t url) : m_listener(url) 
{
    m_listener.support(methods::GET, std::bind(&HttpServer::handle_get, this, std::placeholders::_1));
    m_listener.support(methods::POST, std::bind(&HttpServer::handle_post, this, std::placeholders::_1));
    m_listener.support(methods::PUT, std::bind(&HttpServer::handle_put, this, std::placeholders::_1));
    m_listener.support(methods::DEL, std::bind(&HttpServer::handle_delete, this, std::placeholders::_1));
}

/* ------------------------------------ */

// Function to start listening for incoming HTTP requests
void HttpServer::run() 
{
    m_listener.open().then([this](web::http::http_listener::open_result result) 
    {
        if (result.error()) 
        {
            std::cerr << "Error opening listener: " << result.error().message() << std::endl;
        } else 
        {
            std::cout << "Server listening on: " << result.listener().uri().to_string() << std::endl;
        }
    }).wait();
}

/* ------------------------------------ */

// Function to handle GET requests
void HttpServer::handle_get(http_request request) 
{
    int result = m_manage_db.ReadUsersDetails();

    // Construct an HTTP response based on the result
    http_response response;
    if (result == 0) 
    {
        // User details retrieved successfully
        response.set_status_code(status_codes::OK);
        response.set_body("User details retrieved successfully");
    } 
    else 
    {
        // Failed to retrieve user details
        response.set_status_code(status_codes::InternalError);
        response.set_body("Failed to retrieve user details");
    }
    // Send the HTTP response
    request.reply(response);
      
}

/* ------------------------------------ */

// Function to handle POST requests
void HttpServer::handle_post(http_request request) 
{
    int result = m_manage_db.AddUser();

    // Construct an HTTP response based on the result
    http_response response;
    if (result == 0) 
    {
        // User details retrieved successfully
        response.set_status_code(status_codes::OK);
        response.set_body("User details retrieved successfully");
    } 
    else 
    {
        // Failed to retrieve user details
        response.set_status_code(status_codes::InternalError);
        response.set_body("Failed to retrieve user details");
    }
    // Send the HTTP response
    request.reply(response);
}

/* ------------------------------------ */

// Function to handle PUT requests
void HttpServer::handle_put(http_request request) 
{
    int result = m_manage_db.updateUsersDetails();

    // Construct an HTTP response based on the result
    http_response response;
    if (result == 0) 
    {
        // User details retrieved successfully
        response.set_status_code(status_codes::OK);
        response.set_body("User details retrieved successfully");
    } 
    else 
    {
        // Failed to retrieve user details
        response.set_status_code(status_codes::InternalError);
        response.set_body("Failed to retrieve user details");
    }
    // Send the HTTP response
    request.reply(response);
}

/* ------------------------------------ */

// Function to handle DELETE requests
void HttpServer::handle_delete(http_request request) 
{
    int result = m_manage_db.deleteUser();

    // Construct an HTTP response based on the result
    http_response response;
    if (result == 0) 
    {
        // User details retrieved successfully
        response.set_status_code(status_codes::OK);
        response.set_body("User details retrieved successfully");
    } 
    else 
    {
        // Failed to retrieve user details
        response.set_status_code(status_codes::InternalError);
        response.set_body("Failed to retrieve user details");
    }
    // Send the HTTP response
    request.reply(response);}



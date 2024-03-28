#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "user_management.hpp"

#define PORT 8080

int main() 
{
    userManagement test;
    int opt = 1;

    //create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(client_socket == -1)
    {
        std::cerr << "Socket creation failed" << std::endl;
        return 1;
    }

    //initialize servers address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = PORT;
    if(inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0)
    {
        std::cerr << "Invalid address" << std::endl;
        close(client_socket);
        return 1;
    }

     if(connect(client_socket, (struct sockaddr*)&server_address,
        sizeof(server_address)) == -1)
    {
        std::cerr << "Connect failed" << std::endl;
        close(client_socket);
        return 1;
    }

    //send and recieve message from the client
    const char* message = "Hello from client";
    send(client_socket, message, strlen(message), 0);
    std::cout << "Message sent to server" << std::endl;

    char buffer[1024] = {0};
    int valread = read(client_socket, buffer, 1024);
    std::cout << "Server response: " << buffer << std::endl;


    int user_choice = 0;    
    std::cout << "Please enter your chice: " << '\n' << "1 - Add user" << '\n' <<
        "2 - Delete user" << '\n' << "3 - Update user's details" << '\n' <<
        "4 - Read user's data" << '\n' << "5 - get out"<< std::endl;
    std::cin >> user_choice;

    switch (user_choice)
    {
    case(1):
        test.AddUser();
        break;
    case(2):
        test.deleteUser();
        break;
    case(3):
        test.updateUsersDetails();
        break;
    case(4):
        test.ReadUsersDetails();
        break;
    case(5):
        break;
    default:
        std::cout << "Enter a valid choice" << std::endl;
        break;
    }
    
    close(client_socket);
    
    return 0;
}

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#include "user_management.hpp"

#define PORT 8080

int main() 
{
    userManagement test;
    int opt = 1;

    //create socket
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sfd == -1)
    {
        std::cerr << "Socket creation failed" << std::endl;
        return 1;
    }

    if(setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt))) 
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    //initialize servers address
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = PORT;
    address.sin_addr.s_addr = INADDR_ANY;

    if(bind(sfd, (struct sockaddr*)&address, sizeof(address)) == -1)
    {
        std::cerr << "Bind failed" << std::endl;
        close(sfd);
        return 1;
    }

    if(listen(sfd, 3) == -1)
    {
        std::cerr << "Listen failed" << std::endl;
        close(sfd);
        return 1;
    }

    int client_socket = accept(sfd, nullptr, nullptr);
    if(client_socket == -1)
    {
        std::cerr << "Accept failed" << std::endl;
        close(sfd);
        return 1;
    }

    //send and recieve message from the client
    char buffer[1024] = {0};
    int valread = read(client_socket, buffer, 1024);
    std::cout << "Received: " << buffer << std::endl;

    const char* response = "Hello from server";
    send(client_socket, response, strlen(response), 0);
    std::cout << "Response sent" << std::endl;


    close(client_socket);
    close(sfd);

    return 0;
}

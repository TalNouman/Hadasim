Corona Management System

This project implements a Corona management system with server-client communication using sockets. It allows users to perform CRUD (Create, Read, Update, Delete) operations on user data stored in an SQLite database.
Features

    Add User: Add a new user to the database with various details including name, ID, address, contact information, vaccination dates, illness dates, and recovery dates.
    Delete User: Delete a user from the database based on their ID.
    Update User's Details: Update specific details of a user such as name, address, or contact information.
    Read User's Data: Retrieve and display user data from the database based on their ID.

Dependencies

    SQLite3: This project uses SQLite3 as the database management system. Make sure you have SQLite3 installed on your system.

Building and Running

To build the project, follow these steps:

    Compile the source files using a C++ compiler. Make sure to link against the SQLite3 library.

bash

g++ -o server_test server_test.cpp user_management.cpp -lsqlite3
g++ -o client_test client_test.cpp user_management.cpp -lsqlite3

    Run the server and client executables in separate terminal windows.

bash

./server_test
./client_test

    Follow the prompts in the client terminal to interact with the user management system.

Usage

    When the client program is executed, it connects to the server and prompts the user to choose from various options such as adding, deleting, updating, or reading user data.
    The server listens for incoming connections, accepts client connections, receives messages from clients, and responds accordingly.



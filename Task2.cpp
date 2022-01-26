#include "Client.h"
#include "Comms.h"
#include "Server.h"
#include <iostream>

//Student Name: Immanuel Godfrey
//Student ID: 21817368
//Course ID: CO650 - Advanced Programming

void displayStudent() 
{
    cout << "//Student Name: Immanuel Godfrey" << endl;
    cout << "//Student ID: 21817368" << endl;
    cout << "//Course ID: CO650 - Advanced Programming" << endl;
    cout << endl;
}

int main()
{
    displayStudent();

    //Creating Dynamic client and server objects
    Server* myServer;
    myServer = new Server();

    Client* myClient;
    myClient = new Client();

    //loads object DLL
    myServer->loadDLL();
    myClient->loadDLL();

    //creates object Socket
    myServer->createSocket();
    myClient->createSocket();

    //connects client and server objects
    myServer->bindSocket();
    myClient->connectServer();
    myServer->acceptConnection();
    
    //loops chat app until 'quit' message entry
    while (true)
    {
        //sends data from client to server object
        if (myClient->sendMsg() == false) { break; }

        //server object recieves data from client object
        if (myServer->recieveMsg() == false) { break; }

        //sends data from server to client object
        if (myServer->sendMsg() == false) { break; }

        //client objects recieves data from server object
        if (myClient->recieveMsg() == false) { break; }
    }
    

    myClient->closeSocket();
    myServer->closeSocket();
   
  
}
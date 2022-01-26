#pragma once
#include "Comms.h"
#include "Server.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <tchar.h>
#include <iostream>
#include <string>
#pragma comment(lib, "ws2_32.lib")

//Student Name: Immanuel Godfrey
//Student ID: 21817368
//Course ID: CO650 - Advanced Programming

using namespace std;

class Client
	:public Comms
{
private:
	int port;
	SOCKET cSocket;
	sockaddr_in clientService;
	char Messages[2000];

	const WORD wVersionRequested = MAKEWORD(2, 2);
	int wsaerr;
	WSADATA wsaData;
public:
	Client();
	void createSocket();
	void connectServer();
	void loadDLL();
	bool sendMsg();
	bool recieveMsg();
	void closeSocket();

	
};

inline Client::Client() 
{ 
	port = 55555;
	
}

inline void Client::loadDLL()
{
	//loads DLL by Invoking WSAStartup
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0) {
		cout << "The Winsock dll not found!" << endl;
	}
	else {
		/*cout << "The Winsock dll found!" << endl;*/
		cout << "Client DLL Status: " << wsaData.szSystemStatus << endl;
	}

}

inline void Client::createSocket() 
{
	//create socket using protocol
	cSocket = INVALID_SOCKET;
	cSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (cSocket == INVALID_SOCKET) {
		cout << "Error at socket(): " << WSAGetLastError() << endl;
		WSACleanup();
	}
	else {
		cout << "Client socket() is OK!" << endl;
	}


}

inline void Client::connectServer()
{
	//connects to the server 
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &clientService.sin_addr.s_addr);
	clientService.sin_port = htons(port);

	//uses IP address and port data to connect
	//includes connection exception handling code
	if (connect(cSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
		cout << "Client: connect() - Failed to connect." << endl;
		WSACleanup();
	}
	else {
		cout << "Client: connect() is OK." << endl;
		cout << "Client: Can start sending and receiving data..." << endl;
	}

}


inline bool Client::sendMsg()
{
	//sends client data to the server
	string userData;
	cout << "[Client] Enter Message : ";
	std::getline(cin, userData);


	setClientMsg(userData);
	if (getClientMsg().size() > 0)
	{
		// sending message to server using connected socket
		int ClientDesc = send(cSocket, getClientMsg().c_str(), getClientMsg().size() + 1, 0);
		if (ClientDesc == SOCKET_ERROR) { return 0; }
	}
	return true;
}

inline bool Client::recieveMsg()
{

	// freeing up memory for later use
	ZeroMemory(Messages, 2000);

	// getting messages sent from server using connected socket
	int RecSize = recv(cSocket, Messages, 2000, 0);

	if (RecSize > 0)
	{
		// printing message from server
		cout << "[Client] Server Output : " << string(Messages, 0, RecSize) << endl;
		cout << endl;
		
		//terminates app and display the respective system that initiated shutdown (Client/Server)
		if (string(Messages, 0, RecSize) == "quit")
		{
			cout << "[Server]->Initiating Shutdown... " << endl;
			return 0;
		}
	}
	
	return true;
}

inline void Client::closeSocket()
{
	closesocket(cSocket);
	//frees the dll once the counter reaches zero.
	WSACleanup();
}

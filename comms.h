#pragma once
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <tchar.h>
#include "iostream"
#pragma comment(lib, "ws2_32.lib")

//Student Name: Immanuel Godfrey
//Student ID: 21817368
//Course ID: CO650 - Advanced Programming


using namespace std;
class Comms
{
private:
	string Message;
public:
	Comms();
	~Comms();
	virtual void loadDLL() = 0;
	virtual void createSocket() = 0;
	virtual bool sendMsg() = 0;
	virtual bool recieveMsg() = 0;
	void setClientMsg(string msg);
	string getClientMsg() const;
	virtual void closeSocket() = 0;

};

inline Comms::Comms() {

}

inline Comms::~Comms()
{
}

//Setter memeber function for Message string
inline void Comms::setClientMsg(string msg)
{
	//exception handling for empty messages
	try {
		if (!msg.empty()){Message = msg;}
		else { throw(msg); }
	}
	catch (string msg) { cout << "Text entry must not be empty!" << endl; }
}




//Accessor for Message string
inline string Comms::getClientMsg() const
{
	return Message;
}




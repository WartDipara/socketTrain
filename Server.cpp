#include<stdlib.h>
#include<iostream>
#include<stdio.h>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<cstring>
#pragma comment(lib,"Ws2_32.lib")
using namespace std;

//全局常量

//全局变量
SOCKET serverSock, clientSock;
SOCKADDR_IN serverAddr, clientAddr;

//函数声明

int main() {
	//init dll connection
	WSADATA wsaData;
	int result =WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0) {
		cout << "Socket dll not found!" << endl;
		return 0;
	}
	else {
		cout << "Socket dll connection successed!" << endl;
	}
	
	//create socket
	serverSock=socket(AF_INET,SOCK_STREAM,)
	return 0;
}
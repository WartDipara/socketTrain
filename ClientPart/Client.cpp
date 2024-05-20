#include<stdlib.h>
#include<iostream>
#include<stdio.h>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<cstring>
#pragma comment(lib,"Ws2_32.lib")
using namespace std;

//全局常量
const int BUF_SIZE = 2048;
//全局变量
SOCKET serverSock, clientSock;
SOCKADDR_IN serverService, clientService;
int addrN = sizeof(SOCKADDR_IN);
char sendBuf[BUF_SIZE];//发送缓冲区
char inputBuf[BUF_SIZE];//输入缓冲区
char recvBuf[BUF_SIZE]; //接收缓冲区


int main() {
	WSADATA wsaData;
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0) {
		cout << "Socket dll not found!" << endl;
		return 0;
	}

	clientSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//init client addr
	clientService.sin_addr.s_addr = inet_addr("127.0.0.1");
	clientService.sin_family = AF_INET;
	clientService.sin_port = htons(9905);

	//init server addr
	serverService.sin_addr.s_addr = inet_addr("172.21.99.32");
	serverService.sin_family = AF_INET;
	serverService.sin_port = htons(9905);

	//send message
	while (true) {
		if (connect(clientSock, (sockaddr*)&serverService, sizeof(serverService)) != SOCKET_ERROR) {
			recv(clientSock, recvBuf, BUF_SIZE, 0);
			cout << recvBuf << endl;
		}
	}
	closesocket(serverSock);
	closesocket(clientSock);
	WSACleanup();
	return 0;
}
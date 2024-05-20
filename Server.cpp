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

//函数声明

int main() {
	//init dll connection
	WSADATA wsaData;
	int result =WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0) {
		cout << "Socket dll not found!" << endl;
		WSACleanup();
		return 0;
	}
	
	//create socket
	serverSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//第一个参数 AF=Address Family,INET=ipv4；
	//第二个参数 SOCK_STREAM是流套接字对应TCP协议，而SOCK_DGRAM是报套接字对应UDP协议
	//第三个参数 指定协议，0是随意不指定
	serverService.sin_family = AF_INET;
	serverService.sin_addr.S_un.S_addr = inet_addr("172.21.99.32");
	//宏定义缩写 serverService.sin_addr.s_addr
	serverService.sin_port = htons(9905);

	//bind socket
	bind(serverSock, (sockaddr*)&serverService, sizeof(serverService));

	//listen
	while (true) {
		listen(serverSock, 5); 
		//accept connection
		clientSock=accept(serverSock, (sockaddr*)&clientService, &addrN);
		if (clientSock != INVALID_SOCKET) {
			cout << "Connection successfully!" << endl;
			strcpy(sendBuf, "welcome!");
			send(clientSock, sendBuf, BUF_SIZE, 0);
		}
	}
	closesocket(serverSock);
	closesocket(clientSock);
	WSACleanup();
	return 0;
}
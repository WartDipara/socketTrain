#include <iostream>
#include <string>
#include <Winsock2.h>
#include <WS2tcpip.h>

#pragma comment(lib,"Ws2_32.lib")

using namespace std;
int main2(void) {
	//Initial Winsock
	WSADATA wsaDATA;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaDATA);
	if (iResult != NO_ERROR) {
		wprintf(L"WSAStartup failed with error:%ld\n", iResult);
		return 1;
	}
	//Create socket for listening for incoming connection requests
	SOCKET ListenSocket;
	ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ListenSocket == INVALID_SOCKET) {
		wprintf(L"socket failed with error:%ld\n", WSAGetLastError());
		WSACleanup(); //清理掉
		return 1;
	}
	// The sockaddr_in structure specifies the address family,
	// IP address, and port for the socket that is being bound.
	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_port = htons(9909);
	inet_pton(AF_INET, "127.0.0.1", &service.sin_addr);

	if (bind(ListenSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
		wprintf(L"bind failed with error: %ld\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup(); //清理掉
		return 1;
	}
	//listen
	if (listen(ListenSocket, 1) == SOCKET_ERROR) {
		wprintf(L"listen failed with error: %ld\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	// Create a SOCKET for accepting incoming requests.
	SOCKET AcceptSocket;
	wprintf(L"Waiting for client to connect...\n");

	// Accept the connection.
	AcceptSocket = accept(ListenSocket, NULL, NULL);
	if (AcceptSocket == INVALID_SOCKET) {
		wprintf(L"accept failed with error: %ld\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	else
		wprintf(L"Client connected.\n");

	closesocket(ListenSocket);

	WSACleanup();
	return 0;
}

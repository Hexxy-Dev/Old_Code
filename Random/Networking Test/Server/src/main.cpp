#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "Ws2_32.lib")

int main()
{
	WSADATA wsa;
	SOCKET soc;
	
	printf("\nInitializing Winsock... ");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		printf("WSAStartup failed: %d\n", WSAGetLastError());
		return 1;
	}
	puts("Initialised.\n");
	
	soc = socket(AF_INET, SOCK_STREAM, 0);
	if (soc == INVALID_SOCKET) {
		printf("Could not create socket: %d\n", WSAGetLastError());
		return 1;
	}
	puts("Socket created.\n");


	sockaddr_in server;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_family = AF_INET;
	server.sin_port = htons(70707);

	if (bind(soc, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
		printf("Bind failed with error code : %d\n", WSAGetLastError());
		return 1;
	}
	puts("Bind done");


	listen(soc, 3);
	puts("Waiting for incoming connections...");

	sockaddr_in client;
	int c = sizeof(sockaddr_in);
	SOCKET client_soc = accept(soc, (sockaddr*)&client, &c);
	if (client_soc == INVALID_SOCKET) {
		printf("Accept failed with error code : %d\n", WSAGetLastError());
		return 1;
	}
	puts("Connection accepted");

	char* message = "HELLO FROM SERVER!!";
	send(client_soc, message, strlen(message), 0);
	

	char client_reply[2001];
	int recv_size = recv(client_soc, client_reply, 2000, 0);
	if (recv_size == SOCKET_ERROR) {
		printf("Revieve failed!!\n");
		return 1;
	}
	puts("Reply recieved");
	printf("%d : ", recv_size);
	client_reply[recv_size] = '\0';
	puts(client_reply);

	closesocket(client_soc);
	closesocket(soc);
	WSACleanup();

	std::cin.get();
}
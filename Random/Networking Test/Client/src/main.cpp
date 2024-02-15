#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "Ws2_32.lib")

int main()
{
	WSADATA wsa;
	printf("\nInitializing Winsock... ");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		printf("WSAStartup failed: %d\n", WSAGetLastError());
		return 1;
	}
	puts("Initialised.");


	SOCKET soc;
	soc = socket(AF_INET, SOCK_STREAM, 0);
	if (soc == INVALID_SOCKET) {
		printf("Could not create socket: %d\n", WSAGetLastError());
		return 1;
	}
	puts("Socket created.");


	char* hostname = ""; // REDACTED
	char ip[100];
	struct hostent* he;
	struct in_addr** addr_list;
	int i;

	if ((he = gethostbyname(hostname)) == NULL)
	{
		printf("gethostbyname failed : %d", WSAGetLastError());
		return 1;
	}
	addr_list = (struct in_addr**)he->h_addr_list;

	for (i = 0; addr_list[i] != NULL; i++) {
		strcpy(ip, inet_ntoa(*addr_list[i]));
	}

	printf("%s resolved to : %s\n", hostname, ip);


	sockaddr_in server;
	server.sin_addr.s_addr = inet_addr("");// REDACTED
	server.sin_family = AF_INET;
	server.sin_port = htons(70707);
	if (connect(soc, (sockaddr*)&server, sizeof(server)) < 0) {
		puts("Connection error!!");
		return 1;
	}
	puts("Connected!");


	char* message = "HELLO FROM CLIENT!!!";
	if (send(soc, message, strlen(message), 0) < 0) {
		puts("Send failed!");
		return 1;
	}
	puts("Data sent!!");


	char server_reply[2001];
	int recv_size = recv(soc, server_reply, 2000, 0);
	if (recv_size == SOCKET_ERROR) {
		printf("Revieve failed!!\n");
	}
	puts("Reply recieved");
	printf("%d : ", recv_size);
	server_reply[recv_size] = '\0';
	puts(server_reply);



	closesocket(soc);
	WSACleanup();

	std::cin.get();
}


//int main(int argc, char* argv[])
//{
//	WSADATA wsa;
//	char* hostname = "www.google.com";
//	char ip[100];
//	struct hostent* he;
//	struct in_addr** addr_list;
//	int i;
//
//	printf("\nInitialising Winsock...");
//	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
//	{
//		printf("Failed. Error Code : %d", WSAGetLastError());
//		return 1;
//	}
//	printf("Initialised.\n");
//
//	if ((he = gethostbyname(hostname)) == NULL)
//	{
//		printf("gethostbyname failed : %d", WSAGetLastError());
//		return 1;
//	}
//	addr_list = (struct in_addr**)he->h_addr_list;
//
//	for (i = 0; addr_list[i] != NULL; i++) {
//		//Return the first one;
//		strcpy(ip, inet_ntoa(*addr_list[i]));
//	}
//
//	printf("%s resolved to : %s\n", hostname, ip);
//	return 0;
//}
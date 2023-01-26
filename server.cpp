#include<windows.networking.h>
#include<iostream>
#pragma comment(lib, "Ws2_32.lib")
//port 42069
//local ip is 10.17.68.58
// 0000 1010 0001 0001 0100 0100 0011 1010
// 
//declan ip is 10.17.68.53
//cory ip is 10.17.68.??
//aidan ip is 10.17.68.59

using namespace std;



int main() {

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		return 1;
	}

	struct sockaddr_in server_info = { 0 };

	server_info.sin_family = AF_INET;
	server_info.sin_port = htons(42069);
	int server_info_len = sizeof(server_info);

	struct sockaddr client_info = { 0 };
	int client_info_len = sizeof(client_info);


	SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket < 0) {
		perror("Server socket");
		return -1;
	}


	if (bind(server_socket, (struct sockaddr*)&server_info, server_info_len) < 0) {
		cout << "Definitely failing to bind\n";
		perror("Bind");
		return -1;
	}



	if (listen(server_socket, 0) < 0) {
		perror("Listen");
		return -1;
	}


	SOCKET client_socket = accept(server_socket, &client_info, &client_info_len);

	if (client_socket < 0) {
		perror("Client socket");
		return -1;
	}


	const char* hello = "Connected to Kyle";

	if (send(client_socket, hello, strlen(hello), 0) < 0) {
		perror("Sent");
		return -1;
	}



	closesocket(client_socket);

}
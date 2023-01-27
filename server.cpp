#include<windows.networking.h>
#include<iostream>
#include<string>
#pragma comment(lib, "Ws2_32.lib")
//port 42069
//local ip is 10.17.68.58
//00001010000100010100010000111010
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
	if (server_socket == -1) {
		perror("Server socket");
		return -1;
	}


	if (bind(server_socket, (struct sockaddr*)&server_info, server_info_len) < 0) {
		perror("Bind");
		return -1;
	}



	if (listen(server_socket, 0) < 0) {
		perror("Listen");
		return -1;
	}

	cout << "Listening for client..." << endl;
	SOCKET client_socket = accept(server_socket, &client_info, &client_info_len);

	if (client_socket < 0) {
		perror("Client socket");
		return -1;
	}
	cout << "Connected to client!" << endl;

	char inputText[1500];
	string outputText;

	while (1) {
		cout << "Awaiting client response..." << endl;
		memset(&inputText, 0, sizeof(inputText));//clear the buffer
		recv(client_socket, (char*)&inputText, sizeof(inputText), 0);
		if (!strcmp(inputText, "exit"))
		{
			cout << "Client has quit the session" << endl;
			break;
		}
		cout << "Client: " << inputText << endl;
		cout << ">";
		getline(cin, outputText);
		memset(&inputText, 0, sizeof(inputText)); //clear the buffer
		strcpy_s(inputText, outputText.c_str());
		if (outputText == "exit")
		{
			//send to the client that server has closed the connection
			send(client_socket, (char*)&inputText, strlen(inputText), 0);
			break;
		}
		//send the message to client
		send(client_socket, (char*)&inputText, strlen(inputText), 0);
	}
	closesocket(client_socket);
	closesocket(server_socket);
	cout << "Connection closed." << endl;

}
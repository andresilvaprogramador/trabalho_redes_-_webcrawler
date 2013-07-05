/*
 * http.cpp
 *
 *  Created on: 04/07/2013
 *      Author: andref
 */

using namespace std;


#include "http.h"

http::http() {
	// TODO Auto-generated constructor stub
	this->socket_desc = socket(AF_INET , SOCK_STREAM , 0);

}

http::~http() {
	// TODO Auto-generated destructor stub
}

bool http::Server(string url, int port ) {

}
int main(int argc , char *argv[]) {

	int socket_desc;
	char *message , server_reply[2000];
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);

    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }

    struct sockaddr_in server;

    server.sin_addr.s_addr = inet_addr("74.125.137.94");
    server.sin_family = AF_INET;
    server.sin_port = htons(80);

    if (connect(socket_desc, ( struct sockaddr *) & server, sizeof(server)) > 0) {
        std::cout << "erro de conexao" << std::endl;
    	return 1;
    }
    std::cout << "conectado" << std::endl;

    message = "GET / HTTP/1.1\r\n\r\n";
	if( send(socket_desc , message , strlen(message) , 0) < 0)
	{
		puts("Send failed");
		return 1;
	}
	puts("Data Send\n");

	//Receive a reply from the server
	if( recv(socket_desc, server_reply , 2000 , 0) < 0)
	{
		puts("recv failed");
	}
	puts("Reply received\n");
	//puts(server_reply);

    return 0;
}
#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include <fcntl.h>

int createSocket();

int createNonBlockSocket();

int createHandlingSocket(int listening_socket, sockaddr_in address);

sockaddr_in createSocketAddress(int port);

int bindAddress(int listeing_socket, sockaddr_in server_address);

int listenSocket(int listening_socket);

int convertIP(std::string ip_addr, struct in_addr* address);

int connectServer(int client_socket, sockaddr_in server_address);

int sendMessage(int sending_socket, std::string message);

int recvMessage(int receiving_socket, char *buffer, int buffer_size);

#endif
#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

int createListeningSocket();

int createHandlingSocket(int listening_socket);

sockaddr_in createSocketAddress(int port);

void closeSocket(int socket_1);

int bindAddress(int listeing_socket, sockaddr_in server_address);

int listenSocket(int listening_socket);

int convertIP(char *ip_addr, struct in_addr* address);

int connectServer(int client_socket, sockaddr_in server_address);

int sendMessage(int sending_socket, char *message);

int recvMessage(int receiving_socket, char *buffer, int buffer_size);

//check
void checkCreateSocket(int a_socket);

void checkBindAddress(int bind_result, int listening_socket);

void checkListenSocket(int listening_socket);

void checkConnectClient(int handling_socket, int listening_socket);

void checkConvertIP(int convert_ip, int listening_socket);

void checkConnectServer(int connect_status, int listening_socket);

void checkSendMessage (int msg_sent, int listening_socket);

void checkReceiveMessage (int msg_rcvd, int listening_socket, char* buffer);

#endif
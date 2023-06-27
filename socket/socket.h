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

void showMessage(char *buffer, int usage);

void checkStatus(int broken_socket, int usage);

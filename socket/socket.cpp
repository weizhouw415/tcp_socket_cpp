#include "socket.h"

using namespace std;

int createSocket() {
    int listening_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    return listening_socket;
}

int createNonBlockSocket() {
    int listening_socket = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, IPPROTO_TCP);
    
    // 设置套接字为非阻塞模式
    int flags = fcntl(listening_socket, F_GETFL, 0);
    fcntl(listening_socket, F_SETFL, flags | O_NONBLOCK);

    return listening_socket;
}

int createHandlingSocket(int listening_socket, sockaddr_in address) {
    socklen_t address_length = sizeof(address);
    int handling_socket = accept4(listening_socket, (struct sockaddr *)&address, &address_length, SOCK_NONBLOCK);
    return handling_socket;
}

sockaddr_in createSocketAddress(int port) {
    sockaddr_in socket_address{};
    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = INADDR_ANY;
    socket_address.sin_port = htons(port);  // 设置服务器端口号
    return socket_address;
}

int bindAddress(int listening_socket, sockaddr_in server_address) {
    int bind_result = bind(listening_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    return bind_result;
}

int convertIP(string ip_addr, struct in_addr* address) {
    int conn_server = inet_pton(AF_INET, ip_addr.c_str(), address);
    return conn_server;
}

int connectServer(int client_socket, sockaddr_in server_address) {
    int conn = connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    return conn;
}

int listenSocket(int listening_socket) {
    int listening_status = listen(listening_socket, SOMAXCONN);
    return listening_status;
}

int sendMessage(int sending_socket, string message) {
    int bytes_sent = send(sending_socket, message.c_str(), strlen(message.c_str()), 0);
    return bytes_sent;
}

int recvMessage(int receiving_socket, char *buffer, int buffer_size) {
    memset(buffer, 0, buffer_size);
    int bytes_received = recv(receiving_socket, buffer, buffer_size, 0);
    return bytes_received;
}


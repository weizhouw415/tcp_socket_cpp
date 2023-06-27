#include "socket.h"
#include "../common/message.h"

using namespace std;

int createListeningSocket() {
    int listening_socket = socket(AF_INET, SOCK_STREAM, 0);
    return listening_socket;
}

int createHandlingSocket(int listening_socket) {
    sockaddr_in address{};
    socklen_t address_length = sizeof(address);
    int handling_socket = accept(listening_socket, (struct sockaddr *)&address, &address_length);
    return handling_socket;
}

sockaddr_in createSocketAddress(int port) {
    sockaddr_in socket_address{};
    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = INADDR_ANY;
    socket_address.sin_port = htons(port);  // 设置服务器端口号
    return socket_address;
}

void closeSocket(int socket_1) {
    close(socket_1);
    cout << CORR_CLOSE_SOCKET << endl;
}

int bindAddress(int listening_socket, sockaddr_in server_address) {
    int bind_result = bind(listening_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    return bind_result;
}

int convertIP(char *ip_addr, struct in_addr* address) {
    int conn_server = inet_pton(AF_INET, ip_addr, address);
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

int sendMessage(int sending_socket, char *message) {
    int bytes_sent = send(sending_socket, message, strlen(message), 0);
    return bytes_sent;
}

int recvMessage(int receiving_socket, char *buffer, int buffer_size) {
    memset(buffer, 0, buffer_size);
    int bytes_received = recv(receiving_socket, buffer, buffer_size, 0);
    return bytes_received;
}

void showMessage(char *buffer, int usage) {
    string prefix;
    if (usage == 76)
        prefix = PRE_RECV_MSG;
    else if (usage == 86)
        prefix = PRE_RECV_RPL;
    cout << prefix << buffer << endl;
}

void checkStatus(int broken_socket, int usage) {
    if (broken_socket < 0) {
        if (usage == 71)
            cerr << ERR_CREATE_SOCKET << endl;
        else if (usage == 72)
            cerr << ERR_BIND_ADDRESS << endl;
        else if (usage == 73)
            cerr << ERR_LISTEN_SOCKET << endl;
        else if (usage == 74)
            cerr << ERR_CONN_CLIENT << endl;
        else if (usage == 75)
            cerr << ERR_SEND_REPLY << endl;
        else if (usage == 76)
            cerr << ERR_RECV_MESSAGE << endl;
        else if (usage == 83)
            cerr << ERR_CONV_ADDR << endl;
        else if (usage == 84)
            cerr << ERR_CONN_SERVER << endl;
        else if (usage == 85)
            cerr << ERR_SEND_MESSAGE << endl;
        else if (usage == 86)
            cerr << ERR_RECV_REPLY << endl;
        else
            cerr << ERR_UNKNOWN << endl;
        close(broken_socket);
        exit(1);
    }
    else {
        if (usage == 73)
            cout << CORR_LISTEN_SOCKET << endl;
        else if (usage == 74)
            cout << CORR_CONN_CLIENT << endl;
        else if (usage == 75)
            cout << CORR_SEND_REPLY << endl;
        else if (usage == 84)
            cout << CORR_CONN_SERVER << endl;
        else if (usage == 85)
            cout << CORR_SEND_MESSAGE << endl;
    } 
}
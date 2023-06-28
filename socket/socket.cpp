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

void checkCreateSocket(int a_socket) {
    if (a_socket == -1) {
        cerr << ERR_CREATE_SOCKET << endl;
        close(a_socket);
        exit(1);
    }
}

void checkBindAddress(int bind_result, int listening_socket) {
    if (bind_result == -1) {
        cerr << ERR_BIND_ADDRESS << endl;
        close(listening_socket);
        exit(2);
    }
}

void checkListenSocket(int listening_socket) {
    if (listening_socket == -1) {
        cerr << ERR_LISTEN_SOCKET << endl;
        close(listening_socket);
        exit(3);
    }
    else
        cout << CORR_LISTEN_SOCKET << endl;
}

void checkConnectClient(int handling_socket, int listening_socket) {
    if (handling_socket == -1) {
        cerr << ERR_CONN_CLIENT << endl;
        close(listening_socket);
        exit(4);
    }
    else
        cout << CORR_CONN_CLIENT << endl;
}

void checkConvertIP(int convert_ip, int listening_socket) {
    if (convert_ip == -1) {
        cerr << ERR_CONV_ADDR << endl;
        close(listening_socket);
        exit(5);
    }
}

void checkConnectServer(int connect_status, int listening_socket) {
    if (connect_status == -1) {
        cerr << ERR_CONN_SERVER << endl;
        close(listening_socket);
        exit(6);
    }
    else
        cout << CORR_CONN_SERVER << endl;
}

void checkSendMessage (int msg_sent, int listening_socket) {
    if (msg_sent == -1) {
        cerr << ERR_SEND_MESSAGE << endl;
        close(listening_socket);
        exit(7);
    }
    else
        cout << CORR_SEND_MESSAGE << endl;
}

void checkReceiveMessage (int msg_rcvd, int listening_socket, char* buffer) {
    if (msg_rcvd == -1) {
        cerr << ERR_RECV_MESSAGE << endl;
        close(listening_socket);
        exit(8);
    }
    else
        cout << CORR_RECV_MESSAGE << buffer << endl;
}

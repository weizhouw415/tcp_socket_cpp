#include "check.h"
#include "../common/message.h"

using namespace std;

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

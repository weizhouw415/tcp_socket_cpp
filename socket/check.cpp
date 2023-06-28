#include "check.h"
#include "../common/message.h"

using namespace std;

void checkCreateSocket(int new_socket) {
    if (new_socket == -1) {
        cerr << ERR_CREATE_SOCKET << endl;
        exit(1);
    }
}
    /* 设置套接字为非阻塞模式
    int flags = fcntl(listening_socket, F_GETFL, 0);
    if (flags == -1) {
        std::cerr << "获取套接字标志失败" << std::endl;
        close(listening_socket);
        return 1;
    }
    if (fcntl(listening_socket, F_SETFL, flags | O_NONBLOCK) == -1) {
        std::cerr << "设置套接字为非阻塞模式失败" << std::endl;
        close(listening_socket);
        return 1;
    }   */

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

bool checkConnectClient(int handling_socket) {
    if (handling_socket == -1) {
        if (errno == EWOULDBLOCK || errno == EAGAIN) {
            // 没有新的连接请求，继续循环
            return true;
        }
        cerr << ERR_CONN_CLIENT << endl;
        close(handling_socket);
    }
    else
        cout << CORR_CONN_CLIENT << endl;
    return false;
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
    if (msg_sent == -1)
        cerr << ERR_SEND_MESSAGE << endl;
    else
        cout << CORR_SEND_MESSAGE << endl;
}

void checkReceiveMessage (int msg_rcvd, int listening_socket, char* buffer) {
    if (msg_rcvd == -1) 
        cerr << ERR_RECV_MESSAGE << endl;
    else
        cout << CORR_RECV_MESSAGE << buffer << endl;
}

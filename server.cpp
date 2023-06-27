#include "common/constant.h"
#include "socket/socket.h"

int main(int argc, char* argv[]) {
    // 命令行参数
    int port = atoi(argv[1]);
    char *reply = argv[2];

    // 创建服务器端socket
    int listening_socket = createListeningSocket();
    checkStatus(listening_socket, CREATE_SOCKET);
    
    // 设置服务器地址
    sockaddr_in server_address = createSocketAddress(port);
    
    // 绑定socket到指定地址和端口
    int bind_result = bindAddress(listening_socket, server_address);
    checkStatus(bind_result, BIND_ADDRESS);

    // 开始监听连接
    int listening_status = listenSocket(listening_socket);

    while(true) {
        checkStatus(listening_status, LISTEN_SOCKET);

        // 接受客户端连接
        int handling_socket = createHandlingSocket(listening_socket);
        checkStatus(handling_socket, CONN_CLIENT);
        
        // 接收和处理客户端消息
        char server_buffer[BUFFER_SIZE];
        int msg_rcvd = recvMessage(handling_socket, server_buffer, BUFFER_SIZE);
        checkStatus(msg_rcvd, RECV_MESSAGE);
        showMessage(server_buffer, RECV_MESSAGE);
    
        // 发送回复给客户端
        int reply_sent = sendMessage(handling_socket, reply); 
        checkStatus(reply_sent, SEND_REPLY);

        // 关闭连接和socket
        closeSocket(handling_socket);
    }
    closeSocket(listening_socket);
    
    return 0;
}
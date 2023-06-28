#include "common/constant.h"
#include "socket/socket.h"

int main(int argc, char* argv[]) {
    // 命令行参数
    int port = atoi(argv[1]);
    char *reply = argv[2];

    // 创建服务器端socket
    int listening_socket = createListeningSocket();
    checkCreateSocket(listening_socket);
    
    // 设置服务器地址
    sockaddr_in server_address = createSocketAddress(port);
    
    // 绑定socket到指定地址和端口
    int bind_result = bindAddress(listening_socket, server_address);
    checkBindAddress(bind_result, listening_socket);

    // 开始监听连接
    int listening_status = listenSocket(listening_socket);

    while(true) {
        checkListenSocket(listening_socket);

        // 接受客户端连接
        int handling_socket = createHandlingSocket(listening_socket);
        checkConnectClient(handling_socket, listening_socket);
        
        // 接收和处理客户端消息
        char server_buffer[BUFFER_SIZE];
        int msg_rcvd = recvMessage(handling_socket, server_buffer, BUFFER_SIZE);
        checkReceiveMessage(msg_rcvd, listening_socket, server_buffer);
    
        // 发送回复给客户端
        int reply_sent = sendMessage(handling_socket, reply); 
        checkSendMessage(reply_sent, listening_socket);

        // 关闭连接和socket
        closeSocket(handling_socket);
    }
    closeSocket(listening_socket);
    
    return 0;
}
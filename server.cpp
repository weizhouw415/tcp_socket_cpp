#include "common/constant.h"
#include "socket/socket.h"
#include "socket/check.h"

int main(int argc, char* argv[]) {
    // 命令行参数
    int port = atoi(argv[1]);
    char *reply = argv[2];

    // 设置超时时间为5秒
    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;

    // 创建服务器端socket
    int listening_socket = createNonBlockSocket();
    //int listening_socket = createSocket();
    checkCreateSocket(listening_socket);
    
    // 设置服务器地址
    sockaddr_in server_address = createSocketAddress(port);
    
    // 绑定socket到指定地址和端口
    int bind_result = bindAddress(listening_socket, server_address);
    checkBindAddress(bind_result, listening_socket);

    // 开始监听连接
    int listening_status = listenSocket(listening_socket);
    checkListenSocket(listening_socket);

    while(true) {
        sockaddr_in client_address{};
        int handling_socket = createHandlingSocket(listening_socket, client_address);
        if (checkConnectClient(handling_socket))
            continue;

        // 接收和处理客户端消息
        char server_buffer[BUFFER_SIZE];
        int msg_rcvd = recvMessage(handling_socket, server_buffer, BUFFER_SIZE);
        if (checkReceiveMessage(msg_rcvd, listening_socket, server_buffer))
            continue;
    
        // 发送回复给客户端
        int reply_sent = sendMessage(handling_socket, reply); 
        checkSendMessage(reply_sent, listening_socket);

        // 关闭连接和socket
        close(handling_socket);
    }
    close(listening_socket);
    
    return 0;
}
#include "common/constant.h"
#include "socket/socket.h"
#include "socket/check.h"

int main(int argc, char* argv[]) {
    // 命令行参数
    char *ip_addr = argv[1];
    int port = atoi(argv[2]);
    char *message = argv[3];

    while(true) {
    // 创建客户端socket
    int client_socket = createSocket();
    checkCreateSocket(client_socket);
    
    // 设置服务器地址
    sockaddr_in server_address = createSocketAddress(port);
    int conv_ip = convertIP(ip_addr, &(server_address.sin_addr));
    checkConvertIP(conv_ip, client_socket); 
    
    // 连接到服务器
    int conn_status = connectServer(client_socket, server_address);
    checkConnectServer(conn_status, client_socket); 

    // 发送消息给服务器
    int msg_sent = sendMessage(client_socket, message);
    checkSendMessage(msg_sent, client_socket);
    
    // 接收服务器回复
    char client_buffer[BUFFER_SIZE];
    int reply_rcvd = recvMessage(client_socket, client_buffer, BUFFER_SIZE);
    checkReceiveMessage(reply_rcvd, client_socket, client_buffer);

    // 关闭连接和socket
    close(client_socket);

    sleep(1);
    }

    return 0;
}
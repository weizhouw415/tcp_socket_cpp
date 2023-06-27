#include "common/constant.h"
#include "socket/socket.h"

int main(int argc, char* argv[]) {
    // 命令行参数
    char *ip_addr = argv[1];
    int port = atoi(argv[2]);
    char *message = argv[3];

    // 创建客户端socket
    int client_socket = createListeningSocket();
    checkStatus(client_socket, CREATE_SOCKET);
    
    // 设置服务器地址
    
    sockaddr_in server_address = createSocketAddress(port);
    int conv_ip = convertIP(ip_addr, &(server_address.sin_addr));
    checkStatus(conv_ip, CONV_ADDR); 
    
    // 连接到服务器
    int conn_status = connectServer(client_socket, server_address);
    checkStatus(conn_status, CONN_SERVER); 
    
    // 发送消息给服务器
    int msg_sent = sendMessage(client_socket, message);
    checkStatus(msg_sent, SEND_MESSAGE);
       
    // 接收服务器回复
    char client_buffer[BUFFER_SIZE];
    int reply_rcvd = recvMessage(client_socket, client_buffer, BUFFER_SIZE);
    checkStatus(reply_rcvd, RECV_REPLY);
    showMessage(client_buffer, RECV_REPLY);

    // 关闭连接和socket
    closeSocket(client_socket);
    
    return 0;
}
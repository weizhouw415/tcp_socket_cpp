#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    int port = atoi(argv[1]);

    // 创建服务器套接字
    int serverSocket = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, IPPROTO_TCP);
    if (serverSocket == -1) {
        std::cerr << "Failed to create socket." << std::endl;
        return 1;
    }

    // 设置套接字为非阻塞模式
    int flags = fcntl(serverSocket, F_GETFL, 0);
    if (flags == -1) {
        std::cerr << "Failed to get socket flags." << std::endl;
        return 1;
    }
    if (fcntl(serverSocket, F_SETFL, flags | O_NONBLOCK) == -1) {
        std::cerr << "Failed to set socket to non-blocking mode." << std::endl;
        return 1;
    }


    // 绑定服务器套接字到指定端口
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Failed to bind socket" << std::endl;
        return -1;
    }

    // 监听连接请求
    if (listen(serverSocket, 5) == -1) {
        std::cerr << "Failed to listen on socket" << std::endl;
        return -1;
    }

    // 创建用于存储客户端套接字的数组
    const int MAX_CLIENTS = 10;
    pollfd clientSockets[MAX_CLIENTS];
    memset(clientSockets, 0, sizeof(clientSockets));

    // 将服务器套接字添加到监视列表中
    clientSockets[0].fd = serverSocket;
    clientSockets[0].events = POLLIN;

    while (true) {
        std::cout << std::endl << "Server started, waiting for connections..." << std::endl;

        // 使用poll函数等待文件描述符就绪
        int ready = poll(clientSockets, MAX_CLIENTS, -1);
        if (ready == -1) {
            std::cerr << "Failed to poll sockets" << std::endl;
            break;
        }

        // 检查服务器套接字是否准备好接受新连接
        if (clientSockets[0].revents & POLLIN) {
            // 接受新连接
            sockaddr_in clientAddress{};
            socklen_t clientAddressSize = sizeof(clientAddress);
            int clientSocket = accept4(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressSize, SOCK_NONBLOCK);
            //std::cout << "Created handling socket: " << clientSocket << std::endl;
            if (clientSocket == -1) {
                std::cerr << "Failed to accept client connection" << std::endl;
                continue;
            }

            // 将新连接的套接字添加到监视列表中
            for (int i = 1; i < MAX_CLIENTS; ++i) {
                if (clientSockets[i].fd == 0) {
                    clientSockets[i].fd = clientSocket;
                    clientSockets[i].events = POLLIN;
                    std::cout << "Accepted new connection from "
                              << inet_ntoa(clientAddress.sin_addr)
                              << ":" << ntohs(clientAddress.sin_port) << std::endl;
                    break;
                }
            }
        }

        // 检查客户端套接字是否准备好接收消息
        for (int i = 1; i < MAX_CLIENTS; ++i) {
            //std::cout << "i: " << i << ", clientsocket: " << clientSockets[i].fd << std::endl;
            //std::cout << "listen pollin: " << (clientSockets[0].revents & POLLIN) << "handling pollin: " << (clientSockets[i].revents & POLLIN) << std::endl;
            if (clientSockets[i].fd != 0 && clientSockets[0].revents & POLLIN) {
                char buffer[1024];
                memset(buffer, 0, sizeof(buffer));

                // 接收客户端消息
                int bytesRead = recv(clientSockets[i].fd, buffer, sizeof(buffer), 0);
                if (bytesRead < 0) {
                    // 客户端断开连接
                    std::cout << "Client disconnected" << std::endl;
                } else {
                    // 打印客户端发送的消息
                    std::cout << "Received message from client: " << buffer << std::endl;
                    // 回复客户端
                    std::string reply = "Poll server received your message";
                    int bytes_sent = send(clientSockets[i].fd, reply.c_str(), reply.length(), 0);
                    if (bytes_sent == -1) {
                        std::cerr << "Failed to send message: " << errno << std::endl;
                    }
                    else
                        std::cout << "Successfully send message to client." << std::endl;
                    }
                close(clientSockets[i].fd);
                clientSockets[i].fd = 0;
            }
        }
    }

    // 关闭服务器套接字
    close(serverSocket);

    return 0;
}

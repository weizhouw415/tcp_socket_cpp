#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <errno.h>
#include <cerrno>

int main(int argc, char* argv[]) {
    int port = atoi(argv[1]);

    // 创建套接字;
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

    // 绑定套接字到本地地址和端口
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port); // 这里使用了端口号8080，你可以根据需要修改
    if (bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == -1) {
        std::cerr << "Failed to bind socket: " << errno << std::endl;
        return 1;
    }

    // 监听连接
    if (listen(serverSocket, SOMAXCONN) == -1) {
        std::cerr << "Failed to listen on socket: " << errno << std::endl;
        return 1;
    }
        
    // 创建用于监视的文件描述符集合
    fd_set readSet;
    FD_ZERO(&readSet);
    FD_SET(serverSocket, &readSet);

    // 循环等待和处理消息
    while (true) {
        // 监视文件描述符集合中的可读事件
        std::cout << "\nListening..." << std::endl;
        if (select(serverSocket + 1, &readSet, nullptr, nullptr, nullptr) == -1) {
            std::cerr << "Failed to select: " << errno << std::endl;
            return 1;
        }

        // 检查是否有新的连接请求
        if (FD_ISSET(serverSocket, &readSet)) {
            errno = 0;
            sockaddr_in clientAddress{};
            socklen_t clientAddressSize = sizeof(clientAddress);
            int clientSocket = accept4(serverSocket, reinterpret_cast<sockaddr*>(&clientAddress), &clientAddressSize, SOCK_NONBLOCK);
            if (clientSocket == -1) {
                std::cerr << "Failed to accept client connection:" << errno << std::endl;
                continue;
            }

            // 设置客户端套接字为非阻塞模式
            if (fcntl(clientSocket, F_SETFL, flags | O_NONBLOCK) == -1) {
                std::cerr << "Failed to set client socket to non-blocking mode: " << errno << std::endl;
                return 1;
            }

            // 处理新的客户端连接
            std::cout << "Accepted new client connection." << std::endl;

            // 将客户端套接字添加到监视集合中
            FD_SET(clientSocket, &readSet);
        }

        // 处理已连接的客户端的消息
        for (int clientSocket = serverSocket + 1; clientSocket <= FD_SETSIZE; ++clientSocket) {
            if (FD_ISSET(clientSocket, &readSet)) {
                std::cout << "client socket: " << clientSocket << std::endl;
                char buffer[2048];
                memset(buffer, 0, sizeof(buffer));

                // 读取客户端发送的消息
                ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, MSG_DONTWAIT);
                std::cout << "bytes read: " << bytesRead <<std::endl;
                if (bytesRead == -1) {
                    std::cerr << "Failed to receive data from client: " << errno << std::endl;
                    //continue;
                } else if (bytesRead == 0) {
                    // 客户端关闭了连接
                    std::cout << "Client disconnected... Redirecting...: "  << std::endl;
                    close(clientSocket);
                    FD_CLR(clientSocket, &readSet);
                    continue;
                }

                // 处理接收到的消息 
                if (errno == EAGAIN) {
                    std::cout << "Send error back to client..." << std::endl;
                    char *not_rcvd = "Did not receive the message.";
                    int err_sent = send(clientSocket, not_rcvd, strlen(not_rcvd), 0);
                    continue;
                }
                std::cout << "Received message from client: " << buffer << std::endl;
                char *message = "Hello client! Received your message.";
                int bytes_sent = send(clientSocket, message, strlen(message), 0);
                if (bytes_sent == -1) {
                    std::cerr << "Failed to send message: " << errno << std::endl;
                }
                else
                    std::cout << "Successfully send message to client." << std::endl;
            }
            close(clientSocket);
        }
    }

    // 关闭服务器套接字
    close(serverSocket);

    return 0;
}

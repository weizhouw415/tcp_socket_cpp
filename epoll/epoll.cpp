#include <iostream>
#include <sys/epoll.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <arpa/inet.h>

const int MAX_EVENTS = 10;
const int BUFFER_SIZE = 1024;

int main(int argc, char* argv[]) {
    int port = atoi(argv[1]);

    // 创建监听socket
    int listenSocket = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, IPPROTO_TCP);
    if (listenSocket == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    // 设置监听socket为非阻塞模式
    int flags = fcntl(listenSocket, F_GETFL, 0);
    fcntl(listenSocket, F_SETFL, flags | O_NONBLOCK);

    // 绑定地址和端口
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(port);
    if (bind(listenSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Failed to bind address" << std::endl;
        return 1;
    }

    // 开始监听
    if (listen(listenSocket, 5) == -1) {
        std::cerr << "Failed to listen" << std::endl;
        return 1;
    }

    // 创建epoll实例
    int epollInstance = epoll_create1(0);
    if (epollInstance == -1) {
        std::cerr << "Failed to create epoll instance" << std::endl;
        return 1;
    }

    // 添加监听socket到epoll实例中
    epoll_event event{};
    event.events = EPOLLIN | EPOLLET;  // 监听读事件，使用边缘触发模式
    event.data.fd = listenSocket;
    if (epoll_ctl(epollInstance, EPOLL_CTL_ADD, listenSocket, &event) == -1) {
        std::cerr << "Failed to add listen socket to epoll" << std::endl;
        return 1;
    }

    // 创建用于接收和发送数据的缓冲区
    char buffer[BUFFER_SIZE];

    // 开始事件循环
    epoll_event events[MAX_EVENTS];
    while (true) {
        // 等待事件发生
        std::cout << std::endl << "Listening...Waiting for events..." << std::endl;
        int numEvents = epoll_wait(epollInstance, events, MAX_EVENTS, -1);
        if (numEvents == -1) {
            std::cerr << "Failed to wait for events" << std::endl;
            return 1;
        }

        // 处理所有事件
        for (int i = 0; i < numEvents; ++i) {
            int fd = events[i].data.fd;

            // 如果是监听socket有新连接到达
            if (fd == listenSocket) {
                while (true) {
                    // 接受新连接
                    sockaddr_in clientAddress{};
                    socklen_t clientAddressLength = sizeof(clientAddress);
                    int clientSocket = accept4(listenSocket, (struct sockaddr*)&clientAddress, &clientAddressLength, SOCK_NONBLOCK);
                    if (clientSocket == -1) {
                        // 如果没有新连接，跳出循环
                        if (errno == EAGAIN || errno == EWOULDBLOCK) {
                            std::cerr << errno << " EAGAIN: no new connection" <<std::endl;
                            break;
                        } else {
                            std::cerr << "Failed to accept new connection" << std::endl;
                            return 1;
                        }
                    }
                    std::cout << "create client socket successfully" <<std::endl;

                    // 设置客户端socket为非阻塞模式
                    int flags = fcntl(clientSocket, F_GETFL, 0);
                    fcntl(clientSocket, F_SETFL, flags | O_NONBLOCK);

                    // 将客户端socket添加到epoll实例中
                    event.events = EPOLLIN | EPOLLET;  // 监听读事件，使用边缘触发模式
                    event.data.fd = clientSocket;
                    if (epoll_ctl(epollInstance, EPOLL_CTL_ADD, clientSocket, &event) == -1) {
                        std::cerr << "Failed to add client socket to epoll" << std::endl;
                        return 1;
                    }

                    std::cout << "Accepted new connection from "
                              << inet_ntoa(clientAddress.sin_addr)
                              << ":" << ntohs(clientAddress.sin_port) << std::endl;
                }
            } else {
                // 读取客户端发送的数据
                while (true) {
                    ssize_t bytesRead = recv(fd, buffer, BUFFER_SIZE, 0);
                    if (bytesRead == -1) {
                        // 如果没有更多数据可读，跳出循环
                        if (errno == EAGAIN || errno == EWOULDBLOCK) {
                            std::cerr << errno << " EAGAIN: no more data to read" <<std::endl;
                            break;
                        } else {
                            std::cerr << "Failed to read data from client" << std::endl;
                            return 1;
                        }
                    } else if (bytesRead == 0) {
                        // 客户端关闭连接
                        std::cout << "Client disconnected" << std::endl;
                        close(fd);
                        break;
                    } else {
                        // 处理接收到的数据
                        // 这里可以根据具体需求进行处理，比如解析请求、处理逻辑等
                        // 这里简单地将接收到的数据原样发送回客户端
                        ssize_t bytesSent = send(fd, buffer, bytesRead, 0);
                        if (bytesSent == -1) {
                            std::cerr << "Failed to send data to client" << std::endl;
                            return 1;
                        }
                        std::cout << "Send reply successfully" <<std::endl;
                    }
                }
            }
        }
    }

    // 关闭监听socket和epoll实例
    close(listenSocket);
    close(epollInstance);

    return 0;
}

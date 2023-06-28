#ifndef _CHECK_H_
#define _CHECK_H_

#include <iostream>
#include <unistd.h>

//check
void checkCreateSocket(int a_socket);

void checkBindAddress(int bind_result, int listening_socket);

void checkListenSocket(int listening_socket);

void checkConnectClient(int handling_socket, int listening_socket);

void checkConvertIP(int convert_ip, int listening_socket);

void checkConnectServer(int connect_status, int listening_socket);

void checkSendMessage (int msg_sent, int listening_socket);

void checkReceiveMessage (int msg_rcvd, int listening_socket, char* buffer);

#endif
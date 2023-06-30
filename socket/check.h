#ifndef _CHECK_H_
#define _CHECK_H_

#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>

//check
void checkCreateSocket(int a_socket);

void checkBindAddress(int bind_result, int listening_socket);

void checkListenSocket(int listening_socket);

bool checkConnectClient(int handling_socket);

void checkConvertIP(int convert_ip, int listening_socket);

void checkConnectServer(int connect_status, int listening_socket);

void checkSendMessage (int msg_sent, int listening_socket);

bool checkReceiveMessage (int msg_rcvd, int listening_socket, char* buffer);

#endif
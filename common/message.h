#ifndef _MESSAGE_H_
#define _MESSAGE_H_

//成功消息
const char *CORR_CLOSE_SOCKET = "成功关闭套接字";
const char *CORR_LISTEN_SOCKET = "\n正在监听...等待客户端连接...";
const char *CORR_CONN_CLIENT = "成功连接客户端";
const char *CORR_RECV_MESSAGE = "收到的消息: ";
const char *CORR_CONN_SERVER = "成功连接到服务器";
const char *CORR_SEND_MESSAGE = "成功发送消息";

//失败消息
const char *ERR_CREATE_SOCKET = "无法创建套接字";
const char *ERR_BIND_ADDRESS = "绑定失败";
const char *ERR_LISTEN_SOCKET = "监听失败";
const char *ERR_CONN_CLIENT = "接受客户端连接失败";
const char *ERR_RECV_MESSAGE = "接收消息失败";
const char *ERR_CONV_ADDR = "无效的服务器地址";
const char *ERR_CONN_SERVER = "连接服务器失败";
const char *ERR_SEND_MESSAGE = "发送消息失败";

const char *ERR_UNKNOWN = "Internal Error";

#endif
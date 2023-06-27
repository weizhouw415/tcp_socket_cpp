const int BUFFER_SIZE = 1024;

/* check operation code */
/* for server */
const int CREATE_SOCKET = 71;
const int BIND_ADDRESS = 72;
const int LISTEN_SOCKET = 73;
const int CONN_CLIENT = 74;
const int SEND_REPLY = 75;
const int RECV_MESSAGE = 76;

/* for client */
const int CONV_ADDR = 83;
const int CONN_SERVER = 84;
const int SEND_MESSAGE = 85;
const int RECV_REPLY = 86;
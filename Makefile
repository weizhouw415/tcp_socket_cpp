CC = g++
CFLAGS = -std=c++11 -Iheaders/ -Isocket/

all: server client

server: server.cpp 
	$(CC) $(CFLAGS) -o server server.cpp socket/socket.cpp socket/check.cpp

client: client.cpp 
	$(CC) $(CFLAGS) -o client client.cpp socket/socket.cpp socket/check.cpp

clean:
	rm -f server 
	rm -f client
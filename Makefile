CC = g++
CFLAGS = -std=c++11 -Iheaders/ -Isocket/

all: server client

server: server.cpp 
	$(CC) $(CFLAGS) -o server server.cpp socket/socket.cpp

client: client.cpp 
	$(CC) $(CFLAGS) -o client client.cpp socket/socket.cpp

clean:
	rm -f server 
	rm -f client
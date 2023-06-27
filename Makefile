CC = g++
CFLAGS = -std=c++11 -Iheaders/ -Isocket/

all: server client

server:
	$(CC) $(CFLAGS) -o server server.cpp socket/socket.cpp

client:
	$(CC) $(CFLAGS) -o client client.cpp socket/socket.cpp

clean:
	rm -f server 
	rm -f client
CC = g++
CFLAGS = -std=c++11

all: epoll

epoll: epoll.cpp 
	$(CC) $(CFLAGS) -o server-epoll epoll.cpp

clean:
	rm -f server-epoll

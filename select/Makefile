CC = g++
CFLAGS = -std=c++11 -Iheaders/ -Isocket/

all: select

select: select.cpp 
	$(CC) $(CFLAGS) -o server-sel select.cpp

clean:
	rm -f select
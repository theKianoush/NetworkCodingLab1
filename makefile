# Makefile for client and server

CC = gcc
OBJCS = client1.c
OBJCSS = server1.c

CFLAGS =  -g -Wall
# setup for system
nLIBS =

all: client1 server1

client1: $(OBJCS)
	$(CC) $(CFLAGS) -o $@ $(OBJCS) $(LIBS)

server1: $(OBJCSS)
	$(CC) $(CFLAGS) -o $@ $(OBJCSS) $(LIBS)


clean:
	rm client1 server1

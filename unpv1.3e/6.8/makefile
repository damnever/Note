CC = gcc
CFLAGS = -I$(DIR_LIB)
DIR_LIB = ../lib
LIB_SRC = $(wildcard $(DIR_LIB)/*.c)
LIB_INC = $(wildcard $(DIR_LIB)/*.h)

all:
	make server
	make client

server:
	$(CC) $(CFLAGS) server.c $(LIB_SRC) $(LIB_INC) -o server.exec

client:
	$(CC) $(CFLAGS) client.c $(LIB_SRC) $(LIB_INC) -o client.exec


.PHONY: clean
clean:
	find . -type f -name '*.exec' -exec rm -rf {} +

SOURCES = server.c client.c
OBJECTS = $(SOURCES:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror
.PHONY: all
all: server client
.PHONY: bonus
bonus: server client
server: server.o
    $(CC) -o $@ server.o
client: client.o
    $(CC) -o $@ client.o
.o: .c
    $(CC) -c $(CFLAGS) server.c client.c
.PHONY: clean
clean:
    rm -f $(OBJECTS)
.PHONY: fclean
fclean: clean
    rm -f server client
.PHONY: re
re: fclean all
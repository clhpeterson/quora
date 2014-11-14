CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -g3

SOURCES = nearby.c

OBJECTS = $(SOURCES:.c=.o) ./getLine.o
TARGET = nearby

$(TARGET): $(OBJECTS)
	${CC} ${CFLAGS} -o $@ $^

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

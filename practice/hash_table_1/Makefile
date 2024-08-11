CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
SRC = src
OBJ = obj
SRCS = $(wildcard $(SRC)/*.c) 
BIN_OBJS = $(OBJ)/prime.o $(OBJ)/hash_table.o $(OBJ)/xmalloc.o $(OBJ)/main.o
HPP = include
BINDIR = bin
BIN = $(BINDIR)/hash_table

all: $(BIN)

$(BIN): $(BIN_OBJS)
	$(CC) $(CFLAGS) $(BIN_OBJS) -o $@ -lm

$(OBJ)/%.o: $(SRC)/%.c $(HPP)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ):
	mkdir $@

$(BINDIR):
	mkdir $@

clean:
	$(RM) -r $(BINDIR)/* $(OBJ)/*

CC = gcc
CFLAGS = -g -Wall
SRC = src
OBJ = obj
SRCS = $(wildcard $(SRC)/*.c) 
#BIN_OBJS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
#LIB_OBJS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
BIN_OBJS = $(OBJ)/merge_sort.o $(OBJ)/main.o
LIB_OBJS = $(OBJ)/merge_sort.o

HPP = include

TEST = tests
TESTS = $(wildcard $(TEST)/*.c) 
TESTBINS = $(patsubst $(TEST)/%.c, $(TEST)/bin/%, $(TESTS))

BINDIR = bin
BIN = $(BINDIR)/merge_sort

LIBDIR = lib
LIB = $(LIBDIR)/merge_sort.a

all: $(LIB) $(BIN)

release: CFLAGS = -Wall -O2 -DNDEBUG
release: clean
release: $(LIB)

$(LIB): $(LIBDIR) $(OBJ) $(LIB_OBJS)
	$(RM) $(LIB)
	ar -cvrs $(LIB) $(LIB_OBJS)

$(BIN): $(BIN_OBJS)
	$(CC) $(CFLAGS) $(BIN_OBJS) -o $@

$(OBJ)/%.o: $(SRC)/%.c $(HPP)/%.h
	$(CC) $(CFLAGS) -c $< -o $@ 2>CTE.log

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ 2>CTE.log

$(TEST)/bin/%: $(TEST)/%.c
	$(CC) $(CFLAGS) $< $(LIB_OBJS) -o $@ -lcriterion

$(OBJ):
	mkdir $@

$(LIBDIR):
	mkdir $@

$(BINDIR):
	mkdir $@

$(TEST)/bin:
	mkdir $@

test: $(LIB) $(TEST)/bin $(TESTBINS)
	for test in $(TESTBINS) ; do ./$$test ; done

clean:
	$(RM) -r $(TEST)/bin/* $(LIBDIR)/* $(BINDIR)/* $(OBJ)/*

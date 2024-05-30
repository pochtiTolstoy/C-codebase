CC = gcc
CFLAGS = -g -Wall
SRC = src
OBJ = obj
SRCS = $(wildcard $(SRC)/*.c) 
OBJS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

HPP = include

TEST = tests
TESTS = $(wildcard $(TEST)/*.c) 
TESTBINS = $(patsubst $(TEST)/%.c, $(TEST)/bin/%, $(TESTS))


#BINDIR = bin
#BIN = $(BINDIR)/list

LIBDIR = lib
LIB = $(LIBDIR)/tim_list.a

all: $(LIB)

release: CFLAGS = -Wall -O2 -DNDEBUG
release: clean
release: $(LIB)

$(LIB): $(LIBDIR) $(OBJ) $(OBJS)
	$(RM) $(LIB)
	ar -cvrs $(LIB) $(OBJS)

$(OBJ)/%.o: $(SRC)/%.c $(HPP)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST)/bin/%: $(TEST)/%.c
	$(CC) $(CFLAGS) $< $(OBJS) -o $@ -lcriterion

$(OBJ):
	mkdir $@

$(LIBDIR):
	mkdir $@

$(TEST)/bin:
	mkdir $@

test: $(LIB) $(TEST)/bin $(TESTBINS)
	for test in $(TESTBINS) ; do ./$$test ; done

clean:
	$(RM) -r $(LIBDIR)/* $(OBJ)/*

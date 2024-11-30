CC = gcc
CPPFLAGS = -Isrc/ -Iinclude/ -Itests/
CFLAGS = -Wall -Wextra -Werror -Wvla -std=c99 -pedantic

SRC = src/queue.c
OBJ = $(SRC:.c=.o)

TEST_SRC = tests/test_queue.c
TEST_OBJ = $(TEST_SRC:.c=.o) 
TEST_BIN = test

MAIN_SRC = tests/main.c
MAIN_OBJ = $(MAIN_SRC:.c=.o) 
MAIN_BIN = main

LIB = libqueue.a

all: library

library: $(OBJ)
	ar csr $(LIB) $(OBJ)

debug: CFLAGS += -g3 -fsanitize=address
debug: LDFLAGS += -fsanitize=address
debug: $(MAIN_OBJ) $(OBJ)
	$(CC) $(LDFLAGS) -o $(MAIN_BIN) $(MAIN_OBJ) $(OBJ) $(LDLIBS)

check: CFLAGS += -g3 -fsanitize=address
check: LDFLAGS += -lcriterion -fsanitize=address
check: $(TEST_OBJ) $(OBJ)
	$(CC) $(LDFLAGS) -o $(TEST_BIN) $(TEST_OBJ) $(OBJ) $(LDLIBS)
	./$(TEST_BIN)

gcover: CFLAGS += --coverage -fPIC
gcover: LDLIBS += -lgcov
gcover: check
	gcover --html --html-nested --ouput=report.html

clean:
	$(RM) $(OBJ) $(TEST_OBJ) $(TEST_BIN) $(MAIN_OBJ) $(MAIN_BIN) $(LIB)

.PHONY: clean all check gcover debug

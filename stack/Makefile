CC = gcc
CPPFLAGS = -Isrc/ -Iinclude/ -Itests/
CFLAGS = -Wall -Wextra -Werror -Wvla -std=c99 -pedantic

SRC = src/stack.c
OBJ = $(SRC:.c=.o)

TEST_SRC = tests/test_stack.c
TEST_OBJ = $(TEST_SRC:.c=.o) 
TEST_BIN = test

all: library

library:
	ar csr libsatck.a $(OBJ)

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
	$(RM) $(OBJ) $(TEST_OBJ) $(TEST_BIN) main tests/main.o

.PHONY: clean all check gcover

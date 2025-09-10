CC=cc
CFLAGS=-I./include -Wall -Wextra -Werror -I ../inc
TEST_LIBS=-lcmocka
ARGS_MOCKA= -I$(HOME)/local_libs/include -L$(HOME)/local_libs/lib -lcmocka -Wl,-rpath,$(HOME)/local_libs/lib

#example
all: compile_math

run_test: run_math

compile_math: test_example.c
	$(CC) $(CFLAGS) test_example.c -o test_math $(ARGS_MOCKA)

run_math: compile_math
	./test_math

clean:
	rm -f test_math
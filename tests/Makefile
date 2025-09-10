CC=cc
CFLAGS=-I./include -Wall -Wextra -Werror -I ../inc
TEST_LIBS=-lcmocka
ARGS_MOCKA= -I$(HOME)/local_libs/include -L$(HOME)/local_libs/lib -lcmocka -Wl,-rpath,$(HOME)/local_libs/lib

TESTS = test_example


#example
all: $(TESTS)

test_example: test_example.c
	$(CC) $(CFLAGS) test_example.c -o $@ $(ARGS_MOCKA)

run_example: test_example
	./test_example

# Run all tests
run_test: $(TESTS)
	@for t in $(TESTS); do \
	    echo "Running $$t..."; \
	    ./$$t || exit 1; \
	done
	@echo "All tests passed ✅"
	make clean

clean:
	rm -f $(TESTS)
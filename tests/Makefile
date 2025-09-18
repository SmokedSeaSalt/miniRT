CC=cc
CFLAGS=-I./include -Wall -Wextra -Werror -I ../inc
TEST_LIBS=-lcmocka
ARGS_MOCKA= -I$(HOME)/local_libs/include -L$(HOME)/local_libs/lib -lcmocka -Wl,-rpath,$(HOME)/local_libs/lib

LIBFT_PATH = ../lib/libft
LIBFT = $(LIBFT_PATH)/libft.a
LIBFT_INC = -I $(LIBFT_PATH)/include


TESTS = test_helpers test_math



#example
all: $(TESTS)

libft:
	@make -C $(LIBFT_PATH)

HELPER_FUNC = $(wildcard ../src/helpers/*.c)
HELPER_INC = ../inc

test_helpers: test_helpers.c $(HELPER_FUNC) $(HELPER_INC) libft
	$(CC) $(CFLAGS) $< $(HELPER_FUNC) -I$(HELPER_INC) $(LIBFT) $(LIBFT_INC) -o $@ $(ARGS_MOCKA)

run_helpers: test_helpers
	./test_helpers

MATH_FUNC = $(wildcard ../src/math/*.c)
MATH_INC = ../inc

test_math: test_math.c $(MATH_FUNC) $(MATH_INC) libft
	$(CC) $(CFLAGS) $< $(MATH_FUNC) -I$(MATH_INC) -lm $(LIBFT) $(LIBFT_INC) -o $@ $(ARGS_MOCKA)

run_math: test_math
	./test_math

# Run all tests
run_test: $(TESTS)
	@for t in $(TESTS); do \
	    echo "Running $$t..."; \
	    ./$$t || exit 1; \
	done
	@echo "All tests passed ✅"

clean:
	rm -f $(TESTS)

.PHONY: all test_example run example test_helpers run_helpers run_test clean libft

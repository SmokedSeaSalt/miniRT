CC=cc
CFLAGS=-I./include -Wall -Wextra -Werror -I ../inc -I ../lib/MLX42/include/MLX42 -g -Wno-error=missing-braces
TEST_LIBS=-lcmocka
ARGS_MOCKA= -I$(HOME)/local_libs/include -L$(HOME)/local_libs/lib -lcmocka -Wl,-rpath,$(HOME)/local_libs/lib

LIBFT_PATH = ../lib/libft
LIBFT = $(LIBFT_PATH)/libft.a
LIBFT_INC = -I $(LIBFT_PATH)/include

LIBMLX_PATH = ../lib/MLX42
LIBMLX = $(LIBMLX_PATH)/build/libmlx42.a -ldl -lglfw -pthread -lm
LIBMLX_INC = -I $(LIBMLX_PATH)/include/MLX42

TESTS = test_helpers test_math test_parsing test_intersect test_rendering

all: $(TESTS)

libft:
	@make -C $(LIBFT_PATH)

################################################################################
#                                                                              #
# Test Helpers                                                                 #
#                                                                              #
################################################################################

HELPER_FUNC = $(wildcard ../src/helpers/*.c)
HELPER_INC = ../inc

test_helpers: test_helpers.c $(HELPER_FUNC) $(HELPER_INC) libft
	@$(CC) $(CFLAGS) $< $(HELPER_FUNC) -I$(HELPER_INC) $(LIBFT) $(LIBFT_INC) -o $@ $(ARGS_MOCKA)

run_helpers: test_helpers
	./test_helpers

################################################################################
#                                                                              #
# Test Math                                                                    #
#                                                                              #
################################################################################

MATH_FUNC = $(wildcard ../src/math/*.c)
MATH_INC = ../inc

test_math: test_math.c $(MATH_FUNC) $(MATH_INC) libft
	@$(CC) $(CFLAGS) $< $(MATH_FUNC) -I$(MATH_INC) -lm $(LIBFT) $(LIBFT_INC) -o $@ $(ARGS_MOCKA)

run_math: test_math
	./test_math

################################################################################
#                                                                              #
# Test Parsing                                                                 #
#                                                                              #
################################################################################

PARSING_FUNC = $(wildcard ../src/parsing/*.c) $(wildcard ../src/rendering/*.c) $(HELPER_FUNC) $(MATH_FUNC)
PARSING_INC = ../inc

test_parsing: test_parsing.c $(PARSING_FUNC) $(PARSING_INC) libft
	@$(CC) $(CFLAGS) $< $(PARSING_FUNC) -I$(PARSING_INC) -lm $(LIBFT) $(LIBFT_INC) $(LIBMLX) $(LIBMLX_INC) -o $@ $(ARGS_MOCKA)

run_parsing: test_parsing
	./test_parsing

################################################################################
#                                                                              #
# Test Intersect                                                               #
#                                                                              #
################################################################################

INTERSECT_FUNC = $(wildcard ../src/math/*.c)
INTERSECT_INC = ../inc

test_intersect: test_intersect.c $(INTERSECT_FUNC) $(INTERSECT_INC) libft
	@$(CC) $(CFLAGS) $< $(INTERSECT_FUNC) -I$(INTERSECT_INC) -lm -o $@ $(ARGS_MOCKA)

run_intersect: test_intersect
	./test_intersect

################################################################################
#                                                                              #
# Test Rendering                                                               #
#                                                                              #
################################################################################

RENDERING_FUNC = $(wildcard ../src/rendering/*.c) $(HELPER_FUNC) $(MATH_FUNC)
RENDERING_INC = ../inc

test_rendering: test_rendering.c $(PARSING_FUNC) $(PARSING_INC) libft mlx42
	@$(CC) $(CFLAGS) $< $(RENDERING_FUNC) -I$(RENDERING_INC) -lm $(LIBFT) $(LIBFT_INC) $(LIBMLX) $(LIBMLX_INC) -o $@ $(ARGS_MOCKA)

run_rendering: test_rendering
	./test_rendering

################################################################################
#                                                                              #
# Run all tests                                                                #
#                                                                              #
###########################################################################`#####

run_test: $(TESTS)
	@for t in $(TESTS); do \
	    echo "Running $$t..."; \
	    ./$$t || exit 1; \
	done
	@echo "\033[38:5:2mAll tests passed \033[0m\033[5m✅\033[0m"

clean:
	rm -f $(TESTS)

.PHONY: all test_example run example test_helpers run_helpers run_test clean libft

#libraries
mlx42: | $(LIBMLX_PATH)
	@cmake $(LIBMLX_PATH) -B $(LIBMLX_PATH)/build && make -C $(LIBMLX_PATH)/build -j4

$(LIBMLX_PATH):
	git -c advice.detachedHead=false clone \
		--branch v2.4.1 https://github.com/codam-coding-college/MLX42.git $(LIBMLX_PATH)

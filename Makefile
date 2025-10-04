################################################################################
#                                                                              #
# Basics                                                                       #
#                                                                              #
################################################################################

NAME = miniRT
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
CCDEBUG = -g

################################################################################
#                                                                              #
# Libraries                                                                    #
#                                                                              #
################################################################################

LIB_FOLDER = lib

LIBFT_PATH = lib/libft
LIBFT = $(LIBFT_PATH)/libft.a
LIBFT_INC = -I $(LIBFT_PATH)/include

LIBMLX_PATH = lib/MLX42
LIBMLX = $(LIBMLX_PATH)/build/libmlx42.a -ldl -lglfw -pthread -lm
LIBMLX_INC = -I $(LIBMLX_PATH)/include/MLX42

################################################################################
#                                                                              #
# Source files                                                                 #
#                                                                              #
################################################################################

BUILD_DIR = build
SRC_DIR = src

# C files
SRC = 	src/main.c \
		src/helpers/ft_atof.c \
		src/helpers/ft_split_set.c \
		src/math/intersect_sphere.c \
		src/math/vector3.c \
		src/math/trig.c \
		src/parsing/parse_ambient.c \
		src/parsing/parse_camera.c \
		src/parsing/parse_cylinder.c \
		src/parsing/parse_light.c \
		src/parsing/parse_plane.c \
		src/parsing/parse_sphere.c \
		src/parsing/parsing_helpers.c \
		src/parsing/parsing.c \
		src/parsing/file_handling.c \
		src/rendering/rendering.c \
		src/rendering/ray.c \
		src/rendering/file_output.c \


# Header files
INC = -I inc

OBJ = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))


################################################################################
#                                                                              #
# Rules                                                                        #
#                                                                              #
################################################################################

# Basics
all: mlx42 libft $(NAME)

clean:
	rm -rf $(LIBMLX_PATH)/build
	@make clean -C $(LIBFT_PATH)
	rm -rf $(BUILD_DIR)

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	rm -f $(NAME)

re: fclean all

# Build
$(NAME): $(OBJ)
	@printf "$(COLOUR_BLUE)Compiling miniRT\n$(COLOUR_END)"
	@$(CC) $(CFLAGS) $(OBJ) $(INC) $(LIBFT) $(LIBFT_INC) $(LIBMLX) $(LIBMLX_INC) -lm -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) $(LIBFT_INC) $(LIBMLX_INC) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

# Libraries
mlx42: | $(LIBMLX_PATH)
	@cmake $(LIBMLX_PATH) -B $(LIBMLX_PATH)/build && make -C $(LIBMLX_PATH)/build -j4

$(LIBMLX_PATH):
	git -c advice.detachedHead=false clone \
		--branch v2.4.1 https://github.com/codam-coding-college/MLX42.git $(LIBMLX_PATH)

libft:
	@make -C $(LIBFT_PATH)

# Extra's
debug: fclean

rmmlx42:
	rm -rf $(LIBMLX_PATH)

.PHONY: all clean fclean re mlx42 libft debug rmmlx42 test run_test setup_test \
analyze clean_analisys

################################################################################
#                                                                              #
# Run mac                                                                      #
#                                                                              #
################################################################################

run_mac:
	./miniRT test.rt 1.ppm  && convert 1.ppm 1.png

################################################################################
#                                                                              #
# Testing                                                                      #
#                                                                              #
################################################################################

#unit testing
test:

run_test:
	@make run_test -C tests
	@make clean -C tests

setup_test:
	./tests/setup_tests.sh
#	setup precommit hook
	git config core.hooksPath tests/hooks

#clang testing
analyze:
	@echo "Running static analysis with scan-build..."
	@for srcfile in $(SRC); do \
		objfile=$(BUILD_DIR)/$${srcfile#$(SRC_DIR)/}; \
		objfile=$${objfile%.c}.o; \
		mkdir -p $$(dirname $$objfile); \
		scan-build-14 -o ./reports clang $(CFLAGS) $(INC) $(LIBFT_INC) $(LIBMLX_INC) -c $$srcfile -o $$objfile; \
	done
	@printf "$(COLOUR_BLUE)If bugs were found, reports can be found in /reports\n$(COLOUR_END)"
#	scan-build-14 -o ./reports make all clean


clean_analisys:
	rm -rf reports

################################################################################
#                                                                              #
# Prints                                                                       #
#                                                                              #
################################################################################

# Colours
COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

# Formatting
FORMAT_BOLD=\033[1mBold
FORMAT_NORMAL=\033[0mNormal



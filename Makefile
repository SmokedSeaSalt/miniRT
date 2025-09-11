################################################################################
#                                                                              #
# Basics                                                                       #
#                                                                              #
################################################################################

NAME = miniRT
CC = cc -Wall -Werror -Wextra -lm
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
LIBMLX = $(LIBMLX_PATH)/build/libmlx42.a
LIBMLX_INC = -I $(LIBMLX_PATH)/include

################################################################################
#                                                                              #
# Source files                                                                 #
#                                                                              #
################################################################################

BUILD_FOLDER = build

# C files
#TODO

# Header files
INC = -I inc

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
	rm -rf $(BUILD_FOLDER)

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	rm $(NAME)

re: fclean all

# Build
$(NAME):
#	@$(CC) $(OBJS) $(INC) $(LIBFT_INC) $(LIBMLX_INC) -o $@ && \
	printf "$(COLOUR_BLUE)Compiling: $(notdir $<)\n$(COLOUR_END)"

%.o: %.c | $(BUILD_FOLDER) #TODO

$(BUILD_FOLDER):
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

.PHONY: all clean fclean re mlx42 libft debug


################################################################################
#                                                                              #
# Unit testing                                                                 #
#                                                                              #
################################################################################

test:

run_test:
	@make run_test -C tests

setup_test:
	./tests/setup_tests.sh
#	setup precommit hook
	git config core.hooksPath tests/hooks

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
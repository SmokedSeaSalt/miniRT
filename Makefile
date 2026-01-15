################################################################################
#                                                                              #
# Basics                                                                       #
#                                                                              #
################################################################################

NAME = miniRT
CC = cc
CFLAGS = -Wall -Werror -Wextra -MMD -g

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
		src/helpers/cleanup.c \
		src/helpers/ft_atof.c \
		src/helpers/ft_ftoa.c \
		src/helpers/ft_split_set.c \
		src/helpers/inputs.c \
		src/helpers/main_init.c \
		src/helpers/time.c \
		src/helpers/window_name.c \
		src/math/intersect_cylinder.c \
		src/math/intersect_helpers.c \
		src/math/intersect_plane.c \
		src/math/intersect_sphere.c \
		src/math/vector3_rotate.c \
		src/math/vector3.c \
		src/math/vector4.c \
		src/math/trig.c \
		src/math/vec3_math.c \
		src/math/mat3.c \
		src/math/mat4.c \
		src/parsing/parse_ambient.c \
		src/parsing/parse_camera.c \
		src/parsing/parse_cylinder.c \
		src/parsing/parse_light.c \
		src/parsing/parse_plane.c \
		src/parsing/parse_sphere.c \
		src/parsing/parsing_checks.c \
		src/parsing/parsing_fillers.c \
		src/parsing/parsing_helpers.c \
		src/parsing/parsing.c \
		src/parsing/uv_map_handling.c \
		src/parsing/file_handling.c \
		src/rendering/cylinder.c \
		src/rendering/debug_window.c \
		src/rendering/display_hit_modes.c \
		src/rendering/display_miss_modes.c \
		src/rendering/endcap.c \
		src/rendering/light.c \
		src/rendering/movement.c \
		src/rendering/plane.c \
		src/rendering/ray.c \
		src/rendering/render_pixel.c \
		src/rendering/rendering.c \
		src/rendering/sphere.c \
		src/rendering/uv_mapping/bumpmap.c \
		src/rendering/uv_mapping/cylinder_uv.c \
		src/rendering/uv_mapping/plane_uv.c \
		src/rendering/uv_mapping/sphere_uv.c \
		src/rendering/uv_mapping/uv_mapping.c



# Header files
INC = -I inc

OBJ = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))
DEP = ${OBJ:.o=.d}

################################################################################
#                                                                              #
# Rules                                                                        #
#                                                                              #
################################################################################

# Basics
all: mlx42 libft $(NAME)
	@printf "$(COLOUR_GREEN)Compilation done👍\n$(COLOUR_END)"
clean:
	rm -rf $(LIBMLX_PATH)/build
	@make --no-print-directory clean -C $(LIBFT_PATH)
	rm -rf $(BUILD_DIR)

fclean: clean
	@make --no-print-directory fclean -C $(LIBFT_PATH)
	rm -f $(NAME)

re: fclean all

# Build
$(NAME): Makefile $(OBJ)
	@printf "$(COLOUR_BLUE)Compiling miniRT\n$(COLOUR_END)"
	@$(CC) $(CFLAGS) $(OBJ) $(INC) $(LIBFT) $(LIBFT_INC) $(LIBMLX) $(LIBMLX_INC) -lm -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c Makefile | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	@printf "$(COLOUR_BLUE)Compiling $@ \n$(COLOUR_END)"
	@$(CC) $(CFLAGS) $(INC) $(LIBFT_INC) $(LIBMLX_INC) -c $< -o $@ -MF $(basename $@).d

-include $(DEP)

$(BUILD_DIR):
	mkdir -p $@

# Libraries
mlx42: | $(LIBMLX_PATH)
	@cmake $(LIBMLX_PATH) -B $(LIBMLX_PATH)/build && make --no-print-directory -C $(LIBMLX_PATH)/build -j4

$(LIBMLX_PATH):
	git -c advice.detachedHead=false clone \
		--branch v2.4.1 https://github.com/codam-coding-college/MLX42.git $(LIBMLX_PATH)

libft:
	@printf "$(COLOUR_BLUE)Compiling libft\n$(COLOUR_END)"
	@make --no-print-directory -C $(LIBFT_PATH)

rmmlx42:
	rm -rf $(LIBMLX_PATH)

.PHONY: all clean fclean re mlx42 libft debug rmmlx42

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

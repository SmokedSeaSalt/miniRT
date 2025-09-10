NAME=libft.a
CC=cc
CFLAGS=-Wall -Wextra -Werror

LIBFTPATH= libft/
LIBFTSRCS=	ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_lstnew_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstadd_back_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstiter_bonus.c\
		ft_lstmap_bonus.c
LIBFTALL= $(patsubst %.c, $(LIBFTPATH)%.c, $(LIBFTSRCS))

PRINTFPATH= ft_printf/
PRINTFSRCS= ft_printf.c \
		ft_puts.c \
		print_select1.c \
		print_select2.c
PRINTFALL= $(patsubst %.c, $(PRINTFPATH)%.c, $(PRINTFSRCS))

GNLPATH= get_next_line/
GNLSRCS= get_next_line.c \
		get_next_line_utils.c
GNLALL= $(patsubst %.c, $(GNLPATH)%.c, $(GNLSRCS))

ALLSRCS= $(LIBFTALL) $(PRINTFALL) $(GNLALL)

ALLOBJS= $(patsubst %.c, %.o, $(ALLSRCS))

INCLPATH= include/
INCLSRCS= ft_printf.h \
		get_next_line.h \
		libft.h
INCLALL= $(patsubst %, $(INCLPATH)%, $(INCLSRCS))

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(ALLOBJS) $(INCLALL)
	ar rcsUu $(NAME) $(ALLOBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< -I $(INCLPATH)

clean:
	rm -rf $(ALLOBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

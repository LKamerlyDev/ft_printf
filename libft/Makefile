NAME = libft.a

SRCS_LIBFT =	ft_atoi.c	\
				ft_bzero.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_itoa.c \
				ft_memset.c \
				ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_strchr.c \
				ft_striteri.c \
				ft_putstr_fd.c \
				ft_strdup.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strmapi.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strtrim.c \
				ft_substr.c \
				ft_tolower.c \
				ft_toupper.c \
				ft_calloc.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_split.c \
				ft_lstadd_back.c \
				ft_lstadd_front.c \
				ft_lstclear.c \
				ft_lstdelone.c \
				ft_lstiter.c \
				ft_lstlast.c \
				ft_lstmap.c \
				ft_lstnew.c \
				ft_lstsize.c

include $(DEPS)

CC = cc
DIR_BUILD = .build/
DEPS_FLAGS = -MMD -MP
CFLAGS = -Wall -Werror -Wextra -g3
RM = rm -rf

DIR_INCS = .
INCLUDES = $(addprefix -I, $(DIR_INCS))

OBJS = $(patsubst %.c, $(DIR_BUILD)%.o, $(SRCS_LIBFT))
DEPS = $(patsubst %.c, $(DIR_BUILD)%.d, $(SRCS_LIBFT))

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
	@echo "\033[34m[LIBFT]\033[0m \033[32m$(NAME) created !\033[0m"

$(DIR_BUILD)%.o: $(SRC_PATH)%.c
	@mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) $(DEPS_FLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(DIR_BUILD)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
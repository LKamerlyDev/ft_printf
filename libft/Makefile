NAME = libft.a

include libft.mk
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
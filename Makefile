NAME = libftprintf.a

SRCS	= ft_printf.c	\
			print_functions.c \
			print_ptr.c \
			padding.c \
			itoa_sign.c \
			args_process.c \
			print_hexa.c \
			write.c \
			print_digit.c \

SRCS_BONUS	= ft_printf_bonus.c	\
			print_functions_bonus.c \
			print_ptr_bonus.c \
			padding_bonus.c \
			itoa_sign_bonus.c \
			args_process_bonus.c \
			print_hexa_bonus.c \
			write_bonus.c \
			print_digit_bonus.c 

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
CC = cc
SRC_PATH = src/
SRC_BONUS_PATH = src_bonus/
DIR_BUILD = .build/
DIR_BUILD_BONUS = .build_bonus/
DEPS_FLAGS = -MMD -MP
CFLAGS = -Wall -Werror -Wextra -g3
RM = rm -rf
DIR_INCS = includes/ libft/
INCLUDES = $(addprefix -I, $(DIR_INCS))
LIBFT_OBJS = $(patsubst %.c, libft/$(DIR_BUILD)%.o, $(SRCS_LIBFT))
OBJS = $(patsubst %.c, $(DIR_BUILD)%.o, $(SRCS))
DEPS = $(patsubst %.c, $(DIR_BUILD)%.d, $(SRCS))
OBJS_BONUS = $(patsubst %.c, $(DIR_BUILD_BONUS)%.o, $(SRCS_BONUS))
DEPS_BONUS = $(patsubst %.c, $(DIR_BUILD_BONUS)%.d, $(SRCS_BONUS))
-include $(DEPS) $(DEPS_BONUS)


all: fclean_bonus libft $(NAME)
bonus: fclean_non_bonus libft .bonus_built

libft:
	make -C libft

main:
	$(CC) $(CFLAGS) main.c -L. -l:libftprintf.a $(LIBS) $(INCLUDES)

$(NAME): libft/libft.a $(OBJS)
	ar rcs $(NAME) $(OBJS) $(LIBFT_OBJS)
	@echo "\033[34m[FT_PRINTF]\033[0m \033[32m$(NAME) created !\033[0m"

.bonus_built: libft/libft.a $(OBJS_BONUS)
	ar rcs $(NAME) $(OBJS_BONUS) $(LIBFT_OBJS)
	@echo "\033[34m[FT_PRINTF]\033[0m \033[32m$(NAME) bonus created !\033[0m"
	@touch .bonus_built

$(DIR_BUILD)%.o: $(SRC_PATH)%.c
	@mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) $(DEPS_FLAGS) $(LIBS) $(INCLUDES) -c $< -o $@

$(DIR_BUILD_BONUS)%.o: $(SRC_BONUS_PATH)%.c
	@mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) $(DEPS_FLAGS) $(LIBS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(DIR_BUILD) $(DIR_BUILD_BONUS)

fclean_bonus:
	$(RM) $(DIR_BUILD_BONUS) $(NAME) .bonus_built

fclean_non_bonus:
	$(RM) $(DIR_BUILD) $(NAME) .bonus_built

fclean: fclean_bonus fclean_non_bonus

re: fclean all

.PHONY: all clean fclean fclean_bonus fclean_non_bonus re libft bonus test test_bonus main diff

# for f in src/*.c; do diff "$f" "src_bonus/$(basename ${f%.c})_bonus.c"; done
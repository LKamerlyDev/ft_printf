NAME = libftprintf.a
include libft/libft.mk
include ft_printf.mk
-include $(DEPS) $(DEPS_BONUS)
CC = cc
SRC_PATH = src/
SRC_BONUS_PATH = src_bonus/
DIR_BUILD = .build/
DIR_BUILD_BONUS = .build_bonus/
DEPS_FLAGS = -MMD -MP
CFLAGS = -Wall -Werror -Wextra -g3
RM = rm -rf
LIBS = -Llibft -l:libft.a
DIR_INCS = includes/ libft/
INCLUDES = $(addprefix -I, $(DIR_INCS))
LIBFT_OBJS = $(patsubst %.c, libft/$(DIR_BUILD)%.o, $(SRCS_LIBFT))
OBJS = $(patsubst %.c, $(DIR_BUILD)%.o, $(SRCS))
DEPS = $(patsubst %.c, $(DIR_BUILD)%.d, $(SRCS))
OBJS_BONUS = $(patsubst %.c, $(DIR_BUILD_BONUS)%.o, $(SRCS_BONUS))
DEPS_BONUS = $(patsubst %.c, $(DIR_BUILD_BONUS)%.d, $(SRCS_BONUS))

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

test: $(NAME)
	if [ ! -d "ft_printf_tester" ]; then \
		git clone https://github.com/paulo-santana/ft_printf_tester.git; \
	fi
	cd ./ft_printf_tester && \
	sed -i 's/make -C $${LIBFTPRINTF_DIR}$$/make -C $${LIBFTPRINTF_DIR} bonus/' Makefile && \
	sh ./test a

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
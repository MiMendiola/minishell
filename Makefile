NAME = minishell

# COLORS
RED		=	\033[91;1m
GREEN	=	\033[92;1m
CLEAR	=	\033[0m

CFLAGS = -Wall -Werror -Wextra -g3
CC = cc
AR = ar -crs
RM = rm -f

LIBFTA = libft_ext/libft.a

SRCS = $(addprefix ./src/, so_long.c \
		game/game.c game/message.c game/movements.c\
		map/map_read.c map/map_checker.c \
		sprites/sprite_creator.c sprites/sprite_generator.c sprites/frames_charger.c)

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@make all -sC ./libft_ext
	@echo "$(GREEN)Compiling Libft.$(CLEAR)"
	@make all -sC ./mlx
	@echo "$(GREEN)Compiling Mlx.$(CLEAR)"
	@$(CC) $(CFLAGS) $(OBJS) -I ../../includes/so_long.h $(LIBFTA) $(MLXA) $(MLXFLAGS) -o $(NAME)
	@echo "$(GREEN)So_long Compiled.$(CLEAR)"

clean:
	@$(RM) $(OBJS)
	@make clean -sC libft_ext
	@make clean -sC mlx
	@echo "$(RED)All Objs Deleted.$(CLEAR)"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFTA)
	@echo "$(RED)Everything Deleted.$(CLEAR)"

re: fclean all

.PHONY: all clean fclean re
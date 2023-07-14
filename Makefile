# - * - Makefile - * -

NAME = minishell
CC = @cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
RM = rm -rf

SRC_MSH	=	init.c main.c signals.c prompt.c frees.c list.c
SRC_PRS	=	parse.c parse_split.c parse_split_word.c parse_array.c parse_utils.c
SRC_BLT	=	cmds.c cmds_utils.c export.c unset.c env.c

SRCS	=	$(addprefix src/, $(SRC_MSH))  $(addprefix src/built-ins/, $(SRC_BLT)) \
			$(addprefix src/parser/, $(SRC_PRS))
OBJS	=	$(addprefix $(OBJ_DIR)/, $(SRC_MSH:%.c=%.o)) $(addprefix $(OBJ_DIR)/,  $(SRC_BLT:%.c=%.o)) \
			$(addprefix, $(OBJ_DIR)/, $(SRC_PRS:%.c=%.o))

GREEN	=	"\033[0;32m"
YELLOW	=	"\033[1;33m"
NC		=	"\033[0m"

OBJ_DIR	=	obj
LFT_DIR		=	libft

LIBFT	=	$(LFT_DIR)/libft.a
INC		=	-lreadline

all: $(NAME)

$(LIBFT):
	@make --no-print-directory -C $(LFT_DIR)
	@echo $(GREEN)"Compiled Libft!"$(NC)

$(NAME): $(LIBFT) $(OBJS)
		@$(CC) $(CFLAGS) $(SRCS) $(LIBFT) -o $(NAME) $(INC)
		@echo $(GREEN)"Compiled!"$(NC)

$(OBJ_DIR)/%.o: $(SRCS)
		@mkdir -p $(OBJ_DIR)
		@$(CC) $(CFLAGS) -o $@ -c $<

val: $(NAME)
	@valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --suppressions=readline.supp ./minishell

clean:
		@$(RM) $(OBJS) $(OBJ_DIR)
		@make clean --no-print-directory -C $(LFT_DIR)

fclean: clean
		@$(RM) $(NAME) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re val
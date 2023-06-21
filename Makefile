# - * - Makefile - * -

NAME = minishell
CC = @cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
RM = rm -rf

SRC_MSH	=	init.c main.c signals.c
SRC_PRS	=	parse.c parse_split.c parse_utils_arr.c parse_utils.c

SRCS = $(addprefix src/, $(SRC_MSH)) $(addprefix src/parser/, $(SRC_PRS))
OBJS = $(addprefix, $(OBJS_DIR)/, $(SRC_MSH:%.c=%.o)) $(addprefix, $(OBJS_DIR)/, $(SRC_PRS:%.c=%.o))

GREEN	=	"\033[0;32m"
NC		=	"\033[0m"

OBJS_DIR	=	obj
LFT_DIR		=	libft

INC = -lreadline
LIBFT = $(LFT_DIR)/libft.a

all: $(NAME)

$(LIBFT):
	@make --no-print-directory -C $(LFT_DIR)
	@echo $(GREEN)"Compiled Libft!"$(NC)

$(NAME): $(LIBFT) $(OBJS)
		@$(CC) $(CFLAGS) $(INC) $(SRCS) $(LIBFT) -o $(NAME)
		@echo $(GREEN)"Compiled!"$(NC)

$(OBJS_DIR)/%.o: $(SRCS)
		@mkdir -p $(OBJS_DIR)
		@$(CC) $(CFLAGS) -o $@ -c $<

val: $(NAME)
	@valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --suppressions=readline.supp ./minishell

clean:
		@$(RM) $(OBJS) $(OBJS_DIR)
		@make clean --no-print-directory -C $(LFT_DIR)

fclean: clean
		@$(RM) $(NAME) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re
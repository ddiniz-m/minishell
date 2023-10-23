# - * - Makefile - * -

NAME = minishell
CC = @cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
RM = rm -rf

SRC_MSH	=	frees.c main.c prompt.c signals.c
SRC_BLT	=	cd.c echo.c env.c exit.c export.c pwd.c unset.c
SRC_ERR =	errors.c syntax_errors.c syntax_errors2.c
SRC_EXE =	exec_built_ins.c redirections.c heredoc.c another_run.c #run_pipes.c exec_utils.c exec.c
SRC_PRS	=	parse_counter.c parse_split.c parse_str.c parse.c
SRC_STC	=	cmd_utils.c content.c init.c
SRC_UTL	=	array_utl.c list_utl.c env_utl.c str_utl.c

SRCS	=	$(addprefix src/, $(SRC_MSH)) $(addprefix src/built-ins/, $(SRC_BLT)) \
			$(addprefix src/error_handling/, $(SRC_ERR)) $(addprefix src/exec/, $(SRC_EXE)) \
			$(addprefix src/parser/, $(SRC_PRS)) $(addprefix src/structs/, $(SRC_STC)) \
			$(addprefix src/utils/, $(SRC_UTL))
OBJS	=	$(addprefix $(OBJ_DIR)/, $(SRC_MSH:%.c=%.o)) $(addprefix $(OBJ_DIR)/,  $(SRC_BLT:%.c=%.o)) \
			$(addprefix, $(OBJ_DIR)/, $(SRC_ERR:%.c=%.o))$(addprefix, $(OBJ_DIR)/, $(SRC_EXE:%.c=%.o)) \
			$(addprefix, $(OBJ_DIR)/, $(SRC_PRS:%.c=%.o)) $(addprefix, $(OBJ_DIR)/, $(SRC_STC:%.c=%.o)) \
			$(addprefix, $(OBJ_DIR)/, $(SRC_UTL:%.c=%.o))

GREEN	=	"\033[0;32m"
YELLOW	=	"\033[1;33m"
NC		=	"\033[0m"

OBJ_DIR	=	obj
LFT_DIR	=	libft

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

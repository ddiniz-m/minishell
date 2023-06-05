# - * - Makefile - * -

SRC_MSH = main.c
SRCS = $(addprefix src/, $(SRC_MSH))
OBJS = $(patsubst src/%, $(OBJS_DIR)/%, $(SRCS:%.c=%.o))

OBJS_DIR = obj
INC = -lreadline

NAME = minishell
CC = @cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=thread
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
		@$(CC) $(CFLAGS) $(INC) $(SRCS) -o $(NAME)
		@echo "\033[0;32mCompiled!\033[0m"

$(OBJS_DIR)/%.o: $(SRCS)
		@mkdir -p $(OBJS_DIR)
		@$(CC) $(CFLAGS) -o $@ -c $<

clean:
		@$(RM) $(OBJS) $(OBJS_DIR)

fclean: clean
		@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:01:34 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/19 16:46:09 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//--------------------------------INCLUDES-------------------------------------
#include "../libft/src/libft.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//readline, rl_on_new_line, rl_replace_line, rl_redisplay
#include <readline/readline.h>
#include <readline/history.h>

//opendri, readdir, closedir
#include <sys/types.h>
#include <dirent.h>

//signal
#include <signal.h>

//--------------------------------STRUCT-----------------------------------
typedef struct s_variable
{
	int	words;
}				t_var;

typedef struct s_array
{
	char	**echo;
}				t_arr;

//--------------------------------SRCS-------------------------------------

//cmds_echo.c
int		echo_count(char **arr, int words);
int		echo_word_count(char **arr, int pos, int words);
char	**echo_array(char **arr, int words);
void	echo_struct_init(t_var *var, char **Arr);

//parse_split.c
char	*split_temp(char *str, int word_len);
int		split_word_len(char *str);
char	**split_main(t_var *var, char *str);

//parse_utils.c
int		str_words(char *str);
int		n_char(char *str, char c);
int		meta_char(char c);
/* int		quote_state(char *str, char c); */
int		arr_size(char **arr);
char	**arr_cpy(char **arr, int pos, int size);
void	arr_print(char *str, char **arr);

// parse.c
void	parse_main(t_var *var, char *str);
int		str_words(char *str);

//var_init.c
void	var_init(t_var *var, char *str);

#endif
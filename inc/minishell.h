/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:01:34 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/23 15:18:29 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//----------------------------------INCLUDES------------------------------------
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

//libft
# include "../libft/src/libft.h"

//readline, rl_on_new_line, rl_replace_line, rl_redisplay
# include <readline/readline.h>
# include <readline/history.h>

//signal
# include <signal.h>

//-----------------------------------STRUCT-------------------------------------
typedef struct s_variable
{
	int			words;
	char		**main_arr;
}				t_var;

//------------------------------------SRCS--------------------------------------

// init.c
t_var	*var_struct_init(void);
void	var_init(t_var *var, char *str);

// signals.c
void	signal_init(void);
void	signal_interrupt(int signum);
void	signal_exit(t_var *var, char *str);

// ++++++++++ parser/[.........] ++++++++++
// parse.c
void	parse_main(t_var *var);

// parse_array.c
int		arr_size(char **arr);
char	**arr_cpy(char **arr, int pos, int size);
void	arr_print(char *str, char **arr);
void	arr_free(char **arr);

// parse_split.c
char	*split_temp(char *str, int word_len);
int		split_word(char *str);
char	**split_main(t_var *var, char *str);

// parse_utils.c
void	str_words(t_var *var, char *str);
int		meta_char(char c);

// ++++++++++ built-ins/[.....] ++++++++++
// pwd.c
void	pwd(void);

// cd.c
int		cd(char *path);

#endif

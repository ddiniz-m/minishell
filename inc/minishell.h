/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:01:34 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/07/05 18:14:16 by mira             ###   ########.fr       */
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
	int			cmd_count;
	char		*str;
	char		*prompt;
	char		**env;
	char		**main_arr;
}				t_var;

typedef struct s_array
{
	char		**cmd;
}				t_arr;

//------------------------------------SRCS--------------------------------------

// init.c
t_var	*var_struct_init(void);
void	var_init(t_var *var);

// signals.c
void	signal_init(void);
void	signal_interrupt(int signum);
void	signal_exit(t_var *var);

// prompt.c
char	*set_prompt(t_var *var);

// frees.c
void	free_var(t_var *var);
void	free_array(char **arr);
void	malloc_error(t_var *var);

// ++++++++++ parser/[.........] ++++++++++
// parse.c
void	parse_main(t_var *var);

// parse_array.c
int		arr_size(char **arr);
char	**arr_cpy(char **arr, int pos, int size);
void	arr_print(char *str, char **arr);
char	**arr_add(char **arr, char *str);

// parse_split.c
char	*split_temp(char *str, int word_len);
int		split_word(char *str);
char	**split_main(t_var *var, char *str);

// parse_utils.c
void	str_words(t_var *var, char *str);
int		meta_char(char c);

// ++++++++++ built-ins/[.....] ++++++++++
//cmds_utils.c
int		cmd_count(t_var *var, char **arr);
int		cmd_args(t_var *var, char **arr, int pos);
int		cmd_validate(char *str);

// cmds.c
char	**cmd_array(t_var *var, char **arr, int size);
t_arr	**cmd_struct_init(t_var *var);

//export.c
char	**export_init(t_var *var);
void	export_var(t_var *var);

#endif

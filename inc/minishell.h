/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:01:34 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/13 11:55:14 by ddiniz-m         ###   ########.fr       */
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

//pipex
# include "../src/pipex/pipex.h"

//readline, rl_on_new_line, rl_replace_line, rl_redisplay
# include <readline/readline.h>
# include <readline/history.h>

//signal
# include <signal.h>

//-----------------------------------STRUCT-------------------------------------
typedef struct s_content
{
	char	**cmd_flags;
	char	*cmd_path;
	t_list	*input;
	t_list	*output;
}	t_content;

typedef struct s_cmdlist
{
	t_content			*content;
	struct s_cmdlist	*next;
}	t_cmdlist;

typedef struct s_minishell
{
	int				words;
	int				cmd_count;
	char			**main_arr;
	char			*prompt;
	char			*str;
	t_cmdlist		*cmdlist;
}	t_minishell;

//------------------------------------SRCS--------------------------------------
// signals.c
void		signal_init(void);
void		signal_interrupt(int signum);
void		signal_exit(t_minishell *ms);

// prompt.c
char		*set_prompt(t_minishell *ms);

// frees.c
void		free_ms(t_minishell *ms);
void		free_array(char **arr);
void		free_cmd_list(t_cmdlist *cmdlist);
void		malloc_error(t_minishell *ms);

// +++++++++++++++ struct/[.....] +++++++++++++++
//cmd_utils.c
int			cmd_validate(char *str);
int			cmd_args(char **arr, int pos);
int			cmd_count(t_minishell *ms, char **arr);
char		**cmd_with_flags(char **arr, int pos);
void		cmdlist_print(t_cmdlist **cmdlist);

// init.c
void		var_init(t_minishell *ms);
t_list		*in_lst(char **arr, int cmd_index);
t_list		*out_lst(char **arr, int cmd_index);

// list.c
void		cmd_lstadd_back(t_cmdlist **lst, t_cmdlist *new);
t_cmdlist	*cmd_lstlast(t_cmdlist *lst);
void		list_print(t_list **list);
void		list_sort(t_list **list);
void		list_remove(t_list **list, int pos);
void		list_swap(t_list *list);
int			list_check_dup(t_list **list, char *str);

// +++++++++++++ parser/[.........] +++++++++++++
// parse.clist_print(tmp->content->input);

// parse_array.c
int			arr_size(char **arr);
char		**arr_cpy(char **arr, int pos, int size);
void		arr_print(char *str, char **arr);

// parse_split.c
char		**split_main(t_minishell *ms, char *str);
int			split_word(char *str);
char		*split_temp(char *str, int word_len);

// parse_counter.c
void		str_counter(t_minishell *ms, char *str);

// parse_str.c
int			str_plain(char *str, int i);
int			str_quotes(char *str, char c, int i);
int			str_envar(char *str, int i);
int			str_others(char *str, int i);
int			meta_char(char c);

//parse.c
void		parse_main(t_minishell *ms);

// ++++++++++++++ built-ins/[.....] +++++++++++++
// pwd.c
void		pwd(void);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:01:34 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/03 13:21:41 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//----------------------------------INCLUDES------------------------------------
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <linux/limits.h>
# include <limits.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

//libft
# include "../libft/src/libft.h"

//readline, rl_on_new_line, rl_replace_line, rl_redisplay
# include <readline/readline.h>
# include <readline/history.h>

//signal
# include <signal.h>

//-----------------------------------STRUCT-------------------------------------
typedef struct s_content
{
	int		fd_in;
	int		fd_out;
	t_list	*input;
	t_list	*output;
	t_list	*append;
	t_list	*heredoc;
	char	**cmd_flags;
}	t_content;

typedef struct s_cmdlist
{
	t_content			*content;
	struct s_cmdlist	*next;
}	t_cmdlist;

typedef struct s_minishell
{
	char			*str;
	int				words;
	char			**paths;
	char			*prompt;
	int				fdin_buf;
	int				fdout_buf;
	int				cmd_count;
	char			**main_arr;
	t_cmdlist		*cmdlist;
}	t_minishell;

//------------------------------------SRCS--------------------------------------
// signals.c
void					signal_init(void);
void					signal_interrupt(int signum);
void					signal_exit(t_minishell *ms);

// prompt.c
char					*set_prompt(t_minishell *ms);

// frees.c
void					free_ms(t_minishell *ms);
void					free_array(char **arr);
void					free_cmd_list(t_cmdlist *cmdlist);
void					malloc_error(t_minishell *ms);

// +++++++++++++++ struct/[.....] +++++++++++++++
//cmd_utils.c
void					cmdlist_print(t_cmdlist **cmdlist);
int						cmd_args(char **arr, int pos);
int						cmd_count(char **arr);

//content.c
t_list					*redir_lst(char **arr, int index, char *limiter);
char					**cmd_with_flags(char **arr, int pos);

// init.c
void					var_init(t_minishell *ms);

// list.c
void					list_print(t_list **list);

// +++++++++++++ parser/[.........] +++++++++++++
// parse.clist_print(tmp->content->input);

// array_utils.c
int						arr_size(char **arr);
char					**arr_cpy(char **arr, int pos, int size);
void					arr_print(char *str, char **arr);

// parse_split.c
char					**split_main(t_minishell *ms, char *str);
int						split_word(char *str);
char					*split_temp(char *str, int word_len);

// parse_counter.c
void					str_counter(t_minishell *ms, char *str);

// parse_str.c
int						str_plain(char *str, int i);
int						str_quotes(char *str, char c, int i);
int						str_envar(char *str, int i);
int						str_others(char *str, int i);
int						meta_char(char c);

//parse.c
void					parse_main(t_minishell *ms);

// ++++++++++++++ built-ins/[.....] +++++++++++++
// pwd.c
void					pwd(void);
unsigned long long int	exit_atoull(const char *s);
int						exit_format_error(char *arg);
void					ft_exit(t_minishell *ms, char *arg);

// ++++++++++++++++ utils/[.....] +++++++++++++++

int						arr_size(char **arr);
char					**arr_cpy(char **arr, int pos, int size);
void					arr_print(char *str, char **arr);
void					free_ms(t_minishell *ms);
void					free_array(char **arr);
void					free_list(t_list **list);
void					malloc_error(t_minishell *ms);
void					free_cmd_list(t_cmdlist *cmdlist);

// ++++++++++++++++ exec/[.....] +++++++++++++++

//exe.c
char					**path_init(char **envp);
char					*is_exec(char *str, char **paths);
int						is_built_in(char *str);
void					built_ins(char *builtin);
int						exec(t_cmdlist *cmdlist, char **paths, char **envp);

//open_file.c
int						open_file_in(t_content *content, t_list *lst);
int						open_file_hdoc(t_content *content, t_list *lst);
int						open_file_out(t_content *content, t_list *lst);
int						open_file_app(t_content *content, t_list *lst);

//redir_hdoc
int						run(t_minishell *ms, char **envp);

#endif

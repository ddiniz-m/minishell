/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:01:34 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/07 17:34:21 by ddiniz-m         ###   ########.fr       */
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
typedef struct s_minishell
{
	int			words;
	char		**main_arr;
	char		*prompt;
	char		*str;
	t_cmdtable		*cmd_table;
}	t_minishell;

typedef struct s_cmdtable
{
	t_content	*content;
	t_cmdtable	*next;
}	t_cmdtable;

typedef struct s_list
{
	char	*data;
	t_list	*next;
}	t_list;

typedef struct s_content
{
	t_list	*cmd_flags;
	t_list	*input;
	t_list	*output;
}	t_content;


//------------------------------------SRCS--------------------------------------

// init.c
t_minishell	*struct_init(void);
void	init(t_minishell *ms);

// signals.c
void	signal_init(void);
void	signal_interrupt(int signum);
void	signal_exit(t_minishell *ms);

// prompt.c
char	*set_prompt(t_minishell *ms);

// frees.c
void	free_ms(t_minishell *ms);
void	free_array(char **arr);
void	malloc_error(t_minishell *ms);

// ++++++++++ parser/[.........] ++++++++++
// parse.c
void	parse_main(t_minishell *ms);

// parse_array.c
int		arr_size(char **arr);
char	**arr_cpy(char **arr, int pos, int size);
void	arr_print(char *str, char **arr);

// parse_split.c
char	**split_main(t_minishell *ms, char *str);
int		split_word(char *str);
char	*split_temp(char *str, int word_len);

// parse_counter.c
void	str_counter(t_minishell *ms, char *str);

// parse_str.c
int		str_plain(char *str, int i);
int		str_quotes(char *str, char c, int i);
int		str_envar(char *str, int i);
int		str_others(char *str, int i);
int		meta_char(char c);

// ++++++++++ built-ins/[.....] ++++++++++
// pwd.c
void	pwd(void);

// ++++++++++ libft ++++++++++++++++++

void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), void (*d)(void *));
t_list			*ft_lstnew(char *data);
int				ft_lstsize(t_list *lst);


#endif

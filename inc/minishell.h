/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:01:34 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/08 17:58:53 by ddiniz-m         ###   ########.fr       */
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

//ioctl
//#include <sys/ioctl.h>

//tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
//#include <curses.h>
//#include <term.h>

//tcsetattr, tcgetattr
//#include <termios.h>

//--------------------------------SRCS-------------------------------------

// parse.c
char	*parse_main(char *str);
int		str_words(char *str);

//parse_split.c
char	*split_temp(char *str);
int		split_word_len(char *str);
char	**split(char *str);

//parse_utils.c
int		str_words(char *str);
int		n_char(char *str, char c);
int		quote_state(char *str, char c);
#endif
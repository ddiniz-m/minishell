/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:01:34 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/05 17:03:40 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

#endif
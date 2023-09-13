/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:51:30 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/13 13:05:10 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include <fcntl.h>
# include <stdarg.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

#include "../../inc/minishell.h"

//----------------------------------PIPEX--------------------------------------

char		*get_cmd(char *cmd, char **paths);
char		**path_init(char **envp);

//----------------------------------LIBFT--------------------------------------
char		**ft_split(char const *s, char c);
char		**ft_split2(char const *s, char c);
char		*ft_strnstr(const char *str, const char *to_find, size_t n);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strchr(const char *s, int c);
void		ft_putstr_fd(char *s, int fd);
//----------------------------------PRINTF-------------------------------------
int			ft_printf(const char *str, ...);
int			ft_puthexa(unsigned long long nbr,
				unsigned long long base, int i);
int			ft_check(char str, va_list args);
int			ft_putstr(char *str);
int			ft_putchar(char c);
int			ft_putnbr(int nb);
int			ft_putptr(unsigned long nbr);

#endif
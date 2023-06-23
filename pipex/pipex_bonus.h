/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:51:30 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/04/21 16:09:08 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H

# define PIPEX_BONUS_H

# include <fcntl.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

//----------------------------------PIPEX--------------------------------------
typedef struct s_pipex
{
	int		fd_infile;
	int		fd_outfile;
}			t_pipex;

void		free_arr(char **arr);
char		*get_cmd(char *cmd, char **paths);
char		**path_init(char **envp);

//----------------------------------LIBFT--------------------------------------
char		**ft_split(char const *s, char c);
char		**ft_split2(char const *s, char c);
char		*ft_strnstr(const char *str, const char *to_find, size_t n);
int			ft_strlen(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strchr(const char *s, int c);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:53:16 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/23 13:25:29 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

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
	int		pipefd[2];
	int		fd_infile;
	int		fd_outfile;
}			t_pipex;

void		free_arr(char **arr);
void		close_all(t_pipex *pipex);
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
#endif
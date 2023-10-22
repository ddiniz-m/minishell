/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:46:04 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/22 14:17:24 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* void	change_terminal(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_cc[VQUIT] = _POSIX_VDISABLE;
	tcsetattr(STDIN_FILENO, TCSANOW ,&term);
}

 void	heredoc_child(char *delimiter)
{
	int		hd_fd;
	char	*line;

	line = NULL;
	change_terminal();
	while ((line = get_next_line(STDIN_FILENO)))
	{
		if (ft_strncmp(delimiter, line, ft_strlen(line) - 1) == 0)
		{
			free(line);
			g_exit = 0;
			exit (g_exit);
		}
		ft_putstr_fd(line, fd);
		write(1, "> ", 2);
		free(line);
	}
	exit (g_exit);
}

 void	heredoc(char *delimiter)
{
	pid_t	child;

	write(1, "> ", 2);
	child = fork();
	if (child < 0)
		perror("Minishell: FORK ERROR\n");
	else if (child == 0)
		heredoc_child(delimiter);
	wait(NULL);
}

int	*heredoc(char *delimiter, int *hd_fd)
{
	char	*line;

	if (pipe(hd_fd) < 0)
	{
		printf("Pipe error\n");
		return (NULL);
	}
	line = NULL;
	write(STDOUT_FILENO, "> ", 2);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		printf("LINE: %s", line);
		if (strcmp_nochr(delimiter, line, '\n') == 0)
		{
			free(line);
			return (hd_fd);
		}
		ft_putstr_fd(line, hd_fd[1]);
		write(STDOUT_FILENO, "> ", 2);
		free(line);
	}
	return (hd_fd);
}

 int	*heredoc(char *delimiter, int *hd_fd)
{
	char	*line;
	char	*buf;

	if (pipe(hd_fd) < 0)
	{
		printf("Pipe error\n");
		return (NULL);
	}
	line = NULL;
	while (1)
	{
		buf =  readline("> ");
		line = ft_strjoin(buf,"\n");
		free(buf);
		printf("LINE: %s", line);
		if (strcmp_nochr(delimiter, line, '\n') == 0)
		{
			free(line);
			return (hd_fd);
		}
		ft_putstr_fd(line, hd_fd[1]);
		free(line);
	}
	return (hd_fd);
} */

void	heredoc(char *limiter)
{
	ft_printf("This would be a heredoc: %s\n", limiter);
}

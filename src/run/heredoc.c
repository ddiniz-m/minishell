/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:46:04 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/11/28 12:57:09 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	change_terminal(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_cc[VQUIT] = _POSIX_VDISABLE;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	heredoc_child(t_minishell *ms, int fd, char *limiter)
{
	char	*line;
	char	*limit;

	limit = ft_strdup(limiter);
	free_hdoc(ms);
	line = NULL;
	signal(SIGINT, SIG_DFL);
	change_terminal();
	printf("DELIMITER: %s\n", limit);
	while (1)
	{
		line = readline("> ");
		if (!line)
			heredoc_eof(limit);
		if (!line || strcmp_nochr(limit, line, '\n') == 0)
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
	free(limit);
	if (line)
		free(line);
	close (fd);
	close_fds();
	exit(0);
}

char	*create_file(int here_num)
{
	int		i;
	char	*buf;
	char	*filename;

	i = 0;
	buf = NULL;
	filename = ft_strdup("/tmp/tmpxxx");
	while (i < here_num)
	{
		buf = ft_strdup(filename);
		free(filename);
		filename = ft_strjoin(buf, "x");
		free(buf);
		i++;
	}
	return (filename);
}

char	*heredoc(t_minishell *ms, char *limiter, int here_num)
{
	char	*filename;
	pid_t	pid;
	int		status;
	int		fd;

	signal(SIGINT, SIG_IGN);
	filename = create_file(here_num);
	pid = fork();
	if (pid < 0)
		fork_error(ms, NULL);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd < 0)
		open_error(ms, filename, 1);
	if (pid == 0)
	{
		free(filename);
		heredoc_child(ms, fd, limiter);
	}
	else
	{
		wait(&status);
		if (pid != -1 && WIFSIGNALED(status))
			g_sig = WTERMSIG(status);
	}
	close(fd);
	return (filename);
}

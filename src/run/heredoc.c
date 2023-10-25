/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:46:04 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/25 17:10:29 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	change_terminal(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_cc[VQUIT] = _POSIX_VDISABLE;
	tcsetattr(STDIN_FILENO, TCSANOW ,&term);
}

static void	restore_stdin(void)
{
	int	terminal_fd;

	terminal_fd = open("/dev/tty", O_RDWR);
	if (terminal_fd < 0)
	{
		perror("open failed");
	}
	dup2(terminal_fd, STDIN_FILENO);
	close(terminal_fd);
}

void	heredoc_child(t_minishell *ms, char *file, char *limiter)
{
	char	*line;
	int		fd;

	line = NULL;
	change_terminal();
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd < 0)
		printf("open error\n"); //make actual error function
	write(STDOUT_FILENO, "> ", 2);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		//printf("LINE: %s", line);
		if (strcmp_nochr(limiter, line, '\n') == 0)
			break ;
		ft_putstr_fd(line, fd);
		free(line);
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
	}
	close(fd);
	free(line);
	free_ms(ms);
}

void heredoc(t_minishell *ms, char *limiter)
{
	char	*filename;
	pid_t	pid;
	int		fd;

	filename = "/tmp/tempfilexxxxxxxxxxxxxxxxx";
	restore_stdin();
	pid = fork();
	if (pid < 0)
		printf("fork error\n"); //fork error
	if (pid == 0)
		heredoc_child(ms, filename, limiter);
	else
		waitpid(pid, NULL, 0);
	fd = open(filename, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	unlink("/tmp/tempfilexxxxxxxxxxxxxxxxx");
}

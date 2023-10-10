/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:46:04 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/10 15:40:01 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../gnl/gnl.h"

void	heredoc_child(t_minishell *ms, char *delimiter)
{
	char	*line;
	//char	*buf;

	line = NULL;
	ft_putstr_fd("\n", ms->fd_tmp);
	while ((line = get_next_line(STDIN_FILENO)))
	{
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			ft_putstr_fd(line, ms->fd_tmp);
			free(line);
			exit (0);
		}
		ft_putstr_fd(line, ms->fd_tmp);
		write(1, "> ", 2);
		free(line);
	}
	exit (0);
}

void	heredoc(t_minishell *ms, char *delimiter)
{
	int		i;
	pid_t	child;

	i = 0;
	write(1, "> ", 2);
	child = fork();
	if (child < 0)
		printf("FORK ERROR\n");
	else if (child == 0)
		heredoc_child(ms, delimiter);
	wait(NULL);
}
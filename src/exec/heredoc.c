/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:46:04 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/13 11:49:26 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../gnl/gnl.h"

void	heredoc_child(char *delimiter)
{
	char	*line;

	line = NULL;
	while ((line = get_next_line(STDIN_FILENO)))
	{
		if (ft_strncmp(delimiter, line, ft_strlen(line) - 1) == 0)
		{
			free(line);
			g_exit = 0;
			exit (0);
		}
		write(1, "> ", 2);
		free(line);
	}
	exit (0);
}

void	heredoc(char *delimiter)
{
	int		i;
	pid_t	child;

	i = 0;
	write(1, "> ", 2);
	child = fork();
	if (child < 0)
		printf("FORK ERROR\n");
	else if (child == 0)
		heredoc_child(delimiter);
	wait(NULL);
}
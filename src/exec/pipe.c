/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:27:40 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/03 13:31:06 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	no_pipe(t_minishell *ms, t_cmdlist *cmdlist, char **envp)
{
	pid_t	child;

	redir_in_out(cmdlist->content, ms->main_arr, 0);
	child = fork();
	if (child == 0)
		exec(cmdlist, ms->paths, envp);
	else
	{
		wait(NULL);
		set_fd(ms);
	}
	return (0);
}

int	ft_pipe(t_minishell *ms, t_cmdlist *cmdlist, char **envp, int i)
{
	pid_t	child;
	int		pipe_fd[2];

	if (pipe(pipe_fd) < 0)
	{
		printf("Pipe error\n");
		return (1);
	}
	child = fork();
	if (child == -1)
		return (printf("Fork Error\n"));
	if (child == 0)
		child_process(ms, cmdlist, envp, pipe_fd, i);
	else
		parent_process(pipe_fd);
	return (1);
}

int	run_pipes(t_minishell *ms, t_cmdlist *cmdlist, char **envp, int i)
{
	ft_pipe(ms, cmdlist, envp, i);
	while (ms->main_arr[i] && ft_strcmp(ms->main_arr[i], "|") != 0)
		i++;
	i++;
	return (i);
}

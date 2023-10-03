/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:28:56 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/03 13:42:52 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	child_process(t_minishell *ms, t_cmdlist *cmdlist, char **envp, int *pipe_fd, int i)
{
	if (redir_check(ms))
		redir_in_out(cmdlist->content, ms->main_arr, i);
	else
	{
		close(pipe_fd[0]); 
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	exec(cmdlist, ms->paths, envp);
}

void	parent_process(int *pipe_fd)
{
	close(pipe_fd[1]);
	wait (NULL);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
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

int	run(t_minishell *ms, char **envp)
{
	int			i;
	int			cmds;
	t_cmdlist	*tmp;

	i = 0;
	tmp = ms->cmdlist;
	ms->paths = path_init(envp);
	cmds = ms->cmd_count;
	if (cmds == 1) //if there isn't a pipe
	{
		no_pipe(ms, tmp, envp);
		free_array(ms->paths);
		return (1);
	}
	while (cmds-- > 0) //if there's a pipe
	{
		i = run_pipes(ms, tmp, envp, i);
		if (tmp->next)
			tmp = tmp->next;
	}
	last_cmd(ms, tmp, envp);
	set_fd(ms);
	free_array(ms->paths);
	return (0);
}

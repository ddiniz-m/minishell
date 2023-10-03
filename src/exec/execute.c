/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:28:56 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/03 13:31:10 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec(t_cmdlist *cmdlist, char **paths, char **envp)
{
	char		*cmd_path;

	cmd_path = NULL;
	if (!is_built_in(cmdlist->content->cmd_flags[0]))
		cmd_path = is_exec(cmdlist->content->cmd_flags[0], paths);
	else
	{
		built_ins(cmdlist->content->cmd_flags[0]);
		exit (0);
	}
	if (cmd_path && execve(cmd_path, cmdlist->content->cmd_flags, envp) == -1)
		perror("EXECVE ERROR\n");
	free(cmd_path);
	return (0);
}

int	last_cmd(t_minishell *ms, t_cmdlist *cmdlist, char **envp)
{
	pid_t	child;

	if (cmdlist && !redir_check(ms))
	{
		child = fork();
		if (child == 0)
			exec(cmdlist, ms->paths, envp);
		else
			wait(NULL);
	}
	return (0);
}

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

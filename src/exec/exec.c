/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:48:41 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/03 13:49:01 by ddiniz-m         ###   ########.fr       */
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
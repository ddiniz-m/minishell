/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:48:41 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/03 15:38:28 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**list_to_array(t_list **env)
{
	int		i;
	int		size;
	t_list	*tmp;
	char	**buf;

	i = 0;
	size = ft_lstsize(*env);
	tmp = *env;
	buf = malloc(sizeof(char *) * (size + 1));
	while (tmp && i < size)
	{
		buf[i] = malloc(sizeof(char) * (ft_strlen((char *)tmp->data) + 1));
		ft_strcpy(buf[i], (char *)tmp->data);
		tmp = tmp->next;
		i++;
	}
	return (buf);
}

int	exec(t_minishell *ms, t_cmdlist *cmdlist)
{
	char		*cmd_path;

	cmd_path = NULL;
	if (!is_built_in(cmdlist->content->cmd_flags[0]))
		cmd_path = is_exec(cmdlist->content->cmd_flags[0], ms->paths);
	else
	{
		built_ins(ms, cmdlist->content->cmd_flags[0]);
		exit (0);
	}
	if (cmd_path && execve(cmd_path, cmdlist->content->cmd_flags, list_to_array(ms->env)) == -1)
		perror("EXECVE ERROR\n");
	free(cmd_path);
	return (0);
}
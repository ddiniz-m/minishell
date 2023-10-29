/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_ins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:55:30 by mortins-          #+#    #+#             */
/*   Updated: 2023/10/29 18:27:59 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_built_in(char *str)
{
	if (ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "cd") == 0
		|| ft_strcmp(str, "pwd") == 0 || ft_strcmp(str, "export") == 0
		|| ft_strcmp(str, "unset") == 0 || ft_strcmp(str, "env") == 0
		|| ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}

void	exp_built_in(t_minishell *ms, char **cmd_flags)
{
	if (ft_strcmp(cmd_flags[0], "export") == 0)
	{
		list_sort(ms->exp);
		if (export_error(cmd_flags))
		{
			g_exit = 1;
			return ;
		}
		if (arr_size(cmd_flags) > 1)
			export(cmd_flags, ms->exp, ms->env);
		else
			list_print(ms->exp);
	}
}

void	built_ins(t_minishell *ms, char **cmd_flags, int exit)
{
	if (ft_strcmp(cmd_flags[0], "echo") == 0)
		ft_echo(cmd_flags);
	else if (ft_strcmp(cmd_flags[0], "cd") == 0)
		cd(ms, cmd_flags);
	else if (ft_strcmp(cmd_flags[0], "pwd") == 0)
		pwd();
	else if (ft_strcmp(cmd_flags[0], "exit") == 0)
	{
		if (exit)
			write(STDERR_FILENO, "exit\n", 5);
		ft_exit(ms, cmd_flags);
	}
	else if (ft_strcmp(cmd_flags[0], "env") == 0)
		list_print(ms->env);
	else if (ft_strcmp(cmd_flags[0], "unset") == 0)
		unset(ms->env, ms->exp, cmd_flags);
	else if (ft_strcmp(cmd_flags[0], "export") == 0)
		exp_built_in(ms, cmd_flags);
}

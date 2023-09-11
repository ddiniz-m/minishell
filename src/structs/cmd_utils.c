/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:08:00 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/11 16:53:56 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	cmdlist_print(t_cmdlist **cmdlist)
{
	int			i;
	t_cmdlist	*tmp;


	i = 1;
	tmp = *cmdlist;
	printf("\nLIST:\n");
	while (tmp)
	{
		printf("	NODE%i:\n", i);
		printf("		CONTENT:\n");
		arr_print("	Command with flags", tmp->content->cmd_flags);
		printf("		Input: %s\n", tmp->content->input);
		printf("		Output: %s\n",tmp->content->output);
		i++;
		if (tmp->next)
			tmp = tmp->next;
		else
		{
			printf("NO MORE CMDS\n");
			break ;
		}
	}
}

//Takes main array and position of a command, and returns an array with the
//command and it's flags
char	**cmd_with_flags(char **arr, int pos)
{
	int		i;
	char	**buf;
	int		args;

	i = 0;
	args = cmd_args(arr, pos);
	buf = malloc(sizeof(char *) * (args + 1));
	if (!buf)
		return (NULL);
	while (i < args && arr[pos])
		buf[i++] = arr[pos++];
	buf[i] = NULL;
	return (buf);
}

// Checks if str is a valid command
int	cmd_validate(char *str)
{
	if (ft_strcmp("echo", str) == 0 ||
		ft_strcmp("cd", str) == 0 ||
		ft_strcmp("pwd", str) == 0 ||
		ft_strcmp("unset", str) == 0 ||
		ft_strcmp("env", str) == 0 ||
		ft_strcmp("export", str) == 0 ||
		ft_strcmp("exit", str) == 0)
		return (1);
	return (0);
}

//Counts how many flags/arguments the fisrt command will use/print
int	cmd_args(char **arr, int pos)
{
	int	i;

	i = pos;
	while (arr[i] && i < arr_size(arr))
	{
		if (meta_char(arr[i][0]) == 2)
			break ;
		i++;
	}
	return (i - pos);
}

//Counts how many valied commands there are in main->arr.
int	cmd_count(t_minishell *ms, char **arr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < ms->words)
	{
		if (arr[i] && cmd_validate(arr[i]) == 1)
			j++;
		while (arr && arr[i] && arr[i][0] && meta_char(arr[i][0]) != 2)
			i++;
		i++;
	}
	return (j);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:59:23 by mortins-          #+#    #+#             */
/*   Updated: 2023/11/01 17:12:20 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_heredoc(t_minishell *ms, char **main_arr)
{
	int		index;
	char	*buf;

	index = 0;
	if (!main_arr || !main_arr[0] || !main_arr[0][0])
		return ;
	while (main_arr[index])
	{
		if (ft_strcmp(main_arr[index], "<<") == 0)
		{
			buf = ft_strdup(main_arr[index + 1]);
			free(main_arr[index + 1]);
			main_arr[index + 1] = heredoc(ms, buf, index);
			free(buf);
			index += 2;
		}
		else
			index++;
	}
}

t_list	*redir_lst(char **arr, int index, char *limiter)
{
	t_list	*node;
	t_list	*redir;

	redir = NULL;
	while (arr[index] && ft_strcmp(arr[index], "|") != 0)
	{
		if (ft_strcmp(arr[index], ">|") == 0 || ft_strcmp(arr[index], "<>") \
			== 0)
			arr[index][1] = 0;
		if (ft_strcmp(arr[index], limiter) == 0)
		{
			node = ft_lstnew(arr[index + 1]);
			if (!node)
			{
				ft_lstclear(&redir, free);
				return (NULL);
			}
			ft_lstadd_back(&redir, node);
			index += 2;
		}
		else
			index++;
	}
	return (redir);
}

//Takes main array and position of a command, and returns an array with the
//command and it's flags
char	**cmd_with_flags(t_minishell *ms, char **arr, int pos)
{
	int		i;
	char	**buf;
	int		args;

	i = 0;
	args = cmd_args(arr, pos);
	buf = malloc(sizeof(char *) * (args + 1));
	if (!buf)
		malloc_error(ms);
	while (i < args)
	{
		if (arr[pos] && (ft_strcmp(arr[pos], ">") == 0 \
			|| ft_strcmp(arr[pos], ">>") == 0 || ft_strcmp(arr[pos], "<") == 0 \
			|| ft_strcmp(arr[pos], "<<") == 0))
			pos += 2;
		else if (ft_strcmp(arr[pos], "|") == 0)
			break ;
		else if (arr[pos] && arr[pos][0])
			buf[i++] = arr[pos++];
		else
			pos++;
	}
	buf[i] = NULL;
	return (buf);
}

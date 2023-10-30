/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:59:23 by mortins-          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/10/30 17:16:17 by ddiniz-m         ###   ########.fr       */
=======
/*   Updated: 2023/10/30 18:47:42 by mortins-         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_list	*hdoc_lst(t_minishell *ms, char **arr, int index)
{
	char	*file;
	t_list	*node;
	t_list	*hdoc;

	hdoc = NULL;
	while (arr[index] && ft_strcmp(arr[index], "|") != 0)
	{
		if (ft_strcmp(arr[index], "<<") == 0)
		{
			file = heredoc(ms, arr[index + 1], index);
			node = ft_lstnew(file);
			if (!node)
			{
				ft_lstclear(&hdoc, free);
				return (NULL);
			}
			ft_lstadd_back(&hdoc, node);
			index += 2;
		}
		else
			index++;
	}
	return (hdoc);
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
		if (arr[pos] && (ft_strcmp(arr[pos], ">") == 0 || ft_strcmp(arr[pos], ">>") == 0\
			|| ft_strcmp(arr[pos], "<") == 0 || ft_strcmp(arr[pos], "<<") == 0))
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

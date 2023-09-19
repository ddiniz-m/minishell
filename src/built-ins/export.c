/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:31:09 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/19 15:21:28 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Creates exp array by sorting and editing env
char	**export_array(t_list **list)
{
	int		i;
	int		size;
	char	**exp;
	t_list	*head;
	t_list	*iter;

	i = 0;
	head = *list;
	size = ft_lstsize(*list);
	exp = ft_calloc(size + 1, sizeof(char *));
	while (head && i < size)
	{
		i = 0;
		iter = *list;
		while (iter)
		{
			if (ft_strcmp(head->data, iter->data) > 0)
				i++;
			iter = iter->next;
		}
		exp[i] = head->data;
		head = head->next;
	}
	return (exp);
}

// takes str and creates new string in specific format
// E.g.: str = ARG=123; -> new_str = declare -x ARG="123";
char	*export_str(char *str)
{
	int		i;
	int		j;
	char	*buf1;
	char	*buf2;

	i = 0;
	j = 0;
	buf1 = ft_calloc(ft_strlen(str) + 3, sizeof(char));
	while (str[i] && str[i] != '=')
		buf1[j++] = str[i++];
	buf1[j++] = str[i++];
	buf1[j++] = '\"';
	while (str[i])
		buf1[j++] = str[i++];
	buf1[j] = '\"';
	buf2 = ft_strjoin("declare -x ", buf1);
	free(buf1);
	return (buf2);
}

int	export_check_dup(char *str, t_list **export)
{
	char	*buf;
	t_list	*tmp;

	tmp = *export;
	buf = export_str(str);
	while (tmp)
	{
		if (strcmp_chr(tmp->data, buf, '=') == 0
			|| ft_strcmp(tmp->data, buf) == 0)
		{
			free(buf);
			return (1);
		}
		tmp = tmp->next;
	}
	free(buf);
	return (0);
}

//Checks if there is alredy str in export list;
void	export_override(char *str, t_list **export)
{
	char	*buf;
	t_list	*tmp;

	tmp = *export;
	buf = export_str(str);
	while (tmp)
	{
		if (strcmp_chr(tmp->data, buf, '=') == 0
			|| ft_strcmp(tmp->data, buf) == 0)
			ft_strcpy(tmp->data, buf);
		tmp = tmp->next;
	}
	free(buf);
}

t_list	**export_init(t_list **env)
{
	int		i;
	char	*tmp;
	t_list	**exp;
	t_list	*node;
	char	**env_arr;

	i = 1;
	exp = (t_list **)malloc(sizeof(exp));
	*exp = NULL;
	env_arr = export_array(env);
	while (i < arr_size(env_arr) - 1)
	{
		tmp = export_str(env_arr[i]);
		node = ft_lstnew(tmp);
		ft_lstadd_back(exp, node);
		i++;
	}
	return (exp);
}

void	export(char **arr, t_list **export, t_list **env)
{
	int		i;
	char	*buf;
	t_list	*node;

	i = 1;
	while (i < arr_size(arr))
	{
		buf = ft_strdup(arr[i]);
		if (env_check_dup(buf, env))
			env_override(buf, env);
		if (export_check_dup(buf, export))
		{
			export_override(arr[i++], export);
			continue ;
		}
		if (ft_strchr(buf, '='))
		{
			node = ft_lstnew(buf);
			ft_lstadd_back(env, node);
		}
		node = ft_lstnew(export_str(buf));
		ft_lstadd_back(export, node);
		i++;
	}
}
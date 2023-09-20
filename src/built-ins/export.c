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

t_list	**export_init(t_list **env)
{
	int		i;
	char	*tmp;
	t_list	**exp;
	t_list	*node;
	t_list	*env_buf;

	i = 0;
	exp = (t_list **)malloc(sizeof(exp));
	*exp = NULL;
	env_buf = *env;
	while (i < ft_lstsize(*env))
	{
		tmp = export_str(env_buf->data);
		node = ft_lstnew(tmp);
		ft_lstadd_back(exp, node);
		env_buf = env_buf->next;
		i++;
	}
	list_sort(exp);
	return (exp);
}

// takes str and creates new string in specific format
// E.g.: str = ARG=123; -> new_str = declare -x ARG="123";
char	*export_str(char *str)
{
	int		i;
	int		j;
	int		size;
	char	*buf1;
	char	*buf2;

	i = 0;
	j = 0;
	size = ft_strlen(str);
	buf1 = ft_calloc(size + 3, sizeof(char));
	while (str[i] && str[i] != '=')
		buf1[j++] = str[i++];
	buf1[j++] = str[i++];
	buf1[j++] = '\"';
	while (i < size)
		buf1[j++] = str[i++];
	buf1[j] = '\"';
	buf2 = ft_strjoin("declare -x ", buf1);
	free(buf1);
	return (buf2);
}

int	export_check(char *list_str, char *str)
{
	if (!ft_strchr(str, '='))
		return (1);
	if (strcmp_chr(list_str, str, '=') == 0
		|| ft_strcmp(list_str, str) == 0)
	{
		ft_strcpy(list_str, str);
		return (1);
	}
	return (0);
}

//Checks if there is alredy str in export list;
int	export_override(char *str, t_list **export)
{
	int		i;
	char	*buf;
	t_list	*tmp;

	i = 0;
	tmp = *export;
	buf = export_str(str);
	while (tmp)
	{
		if (export_check(tmp->data, buf))
		{
			free(buf);
			return (1);
		}
		tmp = tmp->next;
		i++;
	}
	free(buf);
	return (0);
}

void	export(char **arr, t_list **export, t_list **env)
{
	int		i;
	char	*buf;
	t_list	*node;

	i = 1;
	buf = NULL;
	while (i < arr_size(arr))
	{
		buf = ft_strdup(arr[i]);
		env_override(buf, env);
		if (export_override(buf, export))
		{
			i++;
			free(buf);
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
		free(buf);
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:55:44 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/11/27 12:16:34 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**var_split(char *str);
char	*var_iter(t_list **env, char *var);

char	*replace_cond(t_minishell *ms, char *str, char *buf1, int flag)
{
	char	*res;
	char	*buf2;

	res = NULL;
	buf2 = NULL;
	if (str[0] == '$')
		res = replace_dollar(ms, str, buf1, flag);
	else if (meta_char(str[0]) == 3)
		res = replace_quotes(ms, str, buf1, flag);
	else if (flag == 2)
	{
		buf2 = add_quotes(str, '\'');
		res = ft_strjoin(buf1, buf2);
		free(buf2);
	}
	else
		res = ft_strjoin(buf1, str);
	return (res);
}

char	*replace_loop(t_minishell *ms, char **arr, int flag)
{
	int		i;
	char	*res;
	char	*buf1;

	i = 0;
	res = NULL;
	while (arr[i])
	{
		buf1 = ft_strdup(res);
		free(res);
		if (flag == 0 && arr_size(arr) >= 2 && ft_strcmp(arr[i], "$") == 0 \
			&& arr[i + 1] && arr[i + 1][0] && (arr[i + 1][0] == '\'' \
			|| arr[i + 1][0] == '\"'))
			res = NULL;
		else if (arr_size(arr) != 1 && (ft_strcmp(arr[i], "\"\"") == 0
				|| ft_strcmp(arr[i], "\'\'") == 0))
			res = ft_strdup(buf1);
		else
			res = replace_cond(ms, arr[i], buf1, flag);
		free(buf1);
		i++;
	}
	return (res);
}

//Joins all substituted strings from the split str
char	*replacer(t_minishell *ms, char *str, int flag)
{
	char	*res;
	char	**arr;

	arr = var_split(str);
	if (!arr)
		return (NULL);
	res = replace_loop(ms, arr, flag);
	free_array(arr);
	return (res);
}

char	**env_var_iter(t_minishell *ms, char **arr)
{
	int		i;
	int		j;
	int		size;
	char	**buf_arr;

	i = 0;
	j = empty_check(ms, arr);
	size = arr_size(arr);
	buf_arr = malloc(sizeof(char *) * (size - j + 1));
	while (j < size)
	{
		if (empty_var(arr[j], ms->env))
		{
			j++;
			continue ;
		}
		buf_arr[i] = replacer(ms, arr[j], 0);
		if (!buf_arr[i++])
			malloc_error(ms);
		j++;
	}
	buf_arr[i] = NULL;
	return (buf_arr);
}

/* If $ is encountered in the array, it replaces the variable with its value
E.g.:
array         new_array
echo   ---->  echo
$HOME  ---->  /ddiniz/home
$VAR   ---->  value */
int	env_var(t_minishell *ms)
{
	t_cmdlist	*cmd_buf;
	char		**buf_arr;
	int			i;
	int			j;

	i = 0;
	cmd_buf = ms->cmdlist;
	while (i < ms->cmd_count)
	{
		j = 0;
		if (arr_size(ms->main_arr) == 1 && empty_var(cmd_buf->cmd_args[0], \
			ms->env))
			return (1);
		buf_arr = arr_dup(ms, cmd_buf->cmd_args);
		free_array(cmd_buf->cmd_args);
		cmd_buf->cmd_args = env_var_iter(ms, buf_arr);
		free_array(buf_arr);
		cmd_buf = cmd_buf->next;
		i++;
	}
	return (0);
}

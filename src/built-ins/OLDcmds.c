/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:10:25 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/07 14:59:56 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//Takes the main array and creates an array with a command and its respective
//	arguments/options
/* char	**cmd_array(t_var *var, char **arr, int size)
{
	int		i;
	char	**buf;
	int		cmd_size;

	i = 0;
	while (i < size)
	{
		if (cmd_validate(arr[i]) == 1)
			break ;
		i++;
		if (i == size)
			return (NULL);
	}
	while (arr[i] != '$' && meta_char(arr[i][0]) != 2)
	{
		
	}
	cmd_size = cmd_args(var, arr, i);
	buf = arr_cpy(arr, i, cmd_size);
	return (buf);
} */

//Takes main array and creates an array for every valid command
/* t_arr	**cmd_struct_init(t_var *var)
{
	int		i;
	t_arr	**arr;
	char	**buf;
	i = 0;
	buf = arr_cpy(var->main_arr, 0, arr_size(var->main_arr));
	arr = malloc(sizeof(t_arr *));
	while (i < var->cmd_count)
	{
		arr[i] = malloc(sizeof(t_arr));
		if (arr && arr[i])
			arr[i]->cmd = cmd_array(var, buf, var->words);
		if (buf)
			buf =  buf + arr_size(arr[i]->cmd) + 1;
		i++;
	}
	return (arr);
} */

//Removes n charcters beginning of from str
char	**array_trim(char **arr, int n)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = malloc(sizeof(char *) * (arr_size(arr)) - n + 1);
	while (i < n)
		i++;
	while (arr[i])
	{
		tmp[i] = arr[i];
		i++;
	}
	arr_print("ARR", arr);
	arr_print("TMP", tmp);
	return (tmp);
}

t_list	*cmd_listnew(char **arr)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	printf("Args = %i\n", cmd_args(arr));
	node->arr = malloc(sizeof(char *) * (cmd_args(arr) + 1));
	if (!node)
		return (NULL);
	node->arr = arr_cpy(arr);
	node->data = NULL;
	node->next = NULL;
	return (node);
}

t_list	**cmd_list_init(t_var *var)
{
	int		i;
	char	**tmp;
	t_list	*node;
	t_list	**cmds;

	i = 0;
	tmp = arr_cpy(var->main_arr);
	cmds = (t_list **)malloc(sizeof(t_list));
	*cmds = NULL;
	while (i < var->cmd_count)
	{
		node = cmd_listnew(tmp);
		arr_print("NODE->ARR", node->arr);
		ft_lstadd_back(cmds, node);
		tmp = array_trim(tmp, cmd_args(tmp));
		arr_print("cmd_list_init TEMP", tmp);
	}
	return (cmds);
}
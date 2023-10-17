/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:21:07 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/17 15:52:02 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//check if there is an echo flag
//Returns 1 if yes, 0 if no
int	echo_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (1);
	i++;
	while (str[i] && str[i] == 'n')
		i++;
	if (str[i])
		return (1);
	return (0);
}

//Returns 1 if there are quotes after str[i]
//Returns 0 otherwise
int	quote_ends(char *str, int i, char c)
{
	i++;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	quote_print_char(char *str, char c, int i)
{
	if (quote_ends(str, i, c))
	{
		i++;
		while (str[i] && str[i] != c)
		{
			printf("%c", str[i++]);
		}
	}
	i++;
	return (i);
}

void	echo_print(char **cmd_flags, int pos)
{
	int		i;
	int		size;

	while (cmd_flags && pos < arr_size(cmd_flags))
	{
		i = 0;
		size = ft_strlen(cmd_flags[pos]);
		while (i < size && cmd_flags[pos][i])
		{
			if (cmd_flags[pos][i] == '\'')
				i = quote_print_char(cmd_flags[pos], '\'', i);
			else if (cmd_flags[pos][i] == '\"')
				i = quote_print_char(cmd_flags[pos], '\"', i);
			else
				printf("%c", cmd_flags[pos][i++]);
		}
		if (ft_strcmp(cmd_flags[pos], "$?") == 0)
			printf("%i", g_exit);
		pos++;
		if (cmd_flags && pos != arr_size(cmd_flags))
			printf(" ");
	}
}

int	echo(char **cmd_flags)
{
	int		j;
	int		cmds;
	int		n_flag;

	j = 1;
	n_flag = 0;
	cmds = cmd_args(cmd_flags, 0);
	if (cmd_flags[1] && echo_flag(cmd_flags[1]) == 0)
	{
		n_flag = 1;
		j++;
	}
	echo_print(cmd_flags, j);
	if (cmds == 1)
		return (printf("\n"));
	if (!n_flag)
		printf("\n");
	g_exit = 0;
	return (0);
}

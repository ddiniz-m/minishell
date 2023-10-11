/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:21:07 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/11 18:02:29 by ddiniz-m         ###   ########.fr       */
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
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	quote_print(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			if (quote_ends(str, i, '\''))
			{
				while (str[i] && str[i] != '\'')
					printf("%c", str[i++]);
			}
		}
		else if (str[i] == '\"')
		{
			i++;
			if (quote_ends(str, i, '\"'))
			{
				while (str[i] && str[i] != '\"')
					printf("%c", str[i++]);
			}
		}
		else
		{
			printf("%c", str[i]);
			i++;
		}
	}
}

void	echo_print(char **cmd_flags, int pos)
{
	char	*buf;

	buf = NULL;
	while (cmd_flags && pos < arr_size(cmd_flags))
	{
		quote_print(cmd_flags[pos]);
		pos++;
		if (cmd_flags && pos != arr_size(cmd_flags))
			printf(" ");
		free(buf);
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
	return (0);
}
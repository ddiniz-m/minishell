/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:57:08 by mortins-          #+#    #+#             */
/*   Updated: 2023/09/07 17:12:39 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	malloc_error(t_var *var)
{
	write(2, "Error: Malloc failed\n", 22);
	free_var(var);
	// Must stop current process and change EXIT_STATUS
}

int	syntax_error(char *str)
{
	int	i;

	i = 0;
	i += quote_error(str);
	i += pipe_error(str);
	i += dollar_error(str);
	return (i); // I think it should change exit status
}

// Checks for unclosed quote marks
int	quote_error(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str && str[i])
	{
		if (meta_char(str[i]) == 3)
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				i++;
			if (!str[i])
			{
				write(1, "MiniShell: syntax error: unclosed quote marks\n", 46);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	pipe_error(char *str)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] && meta_char(str[i]) == 3)
			i = str_quotes(str, str[i], i);
		else if (str[i] && str[i] == '|')
		{
			i++;
			while (str[i] && meta_char(str[i]) == 1)
				i++;
			if (str[i] && str[i] == '|')
			{
				write(1, "MiniShell: syntax error near unexpected token `|`\n", \
					50);
				return (1);
			}
		}
		else
			i++;
	}
	return (0);
}

int	dollar_error(char *str)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (!str[i])
				break ;
			i++;
		}
		else if (str[i] == '$' && str[i + 1] == '$')
		{
			write(1, "MiniShell: syntax error near unexpected token `$`\n", 50);
			return (1);
		}
		else
			i++;
	}
	return (0);
}

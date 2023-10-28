/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:05:56 by mortins-          #+#    #+#             */
/*   Updated: 2023/10/12 17:15:20 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//Checks if there are any >, < or | in sucession (divided by whitespace)
//Example: hello > > world; hello > | world: hello > < world
int	sucession_error(char *str)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(str);
	while (i < size - 1)
	{
		while (i < size && str[i] != '<' && str[i] != '>')
			i++;
		i++;
		if (i < size && meta_char(str[i]) == 1)
			while (str[i] && meta_char(str[i]) == 1)
				i++;
		else
			i++;
		if (i < size && meta_char(str[i]) == 2)
			return (token_message(str[i]));
		i++;
	}
	return (0);
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
				write(2, "MiniShell: syntax error: unclosed quote marks\n", 46);
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
				return (token_message('|'));
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
			return (token_message('$'));
		else
			i++;
	}
	return (0);
}

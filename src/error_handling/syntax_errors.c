/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:44:37 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/18 13:04:11 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	skip_quotes(char *str, int i);
int	skip_quotes_rev(char *str, int size);

//Checks for metachar at the start of str
int	begin_error(char *str)
{
	int	i;

	i = 0;
	while (str[i] && meta_char(str[i]) == 1)
		i++;
	i = skip_quotes(str, i);
	if (str[i] && str[i] == '|')
		return (token_message(str[i]));
	return (0);
}

//Checks for metachar at the end of str
int	end_of_string_error(char *str)
{
	int	size;

	size = ft_strlen(str) - 1;
	while (size >= 0)
	{
		size = skip_quotes_rev(str, size);
		if (str[size] && (str[size] == '<' || str[size] == '>'
			|| str[size] == '|') && str[size] != '\"' && str[size] != '\'')
			return (write(2, \
			"MiniShell: syntax error near unexpected token 'newline'\n", 56));
		if (meta_char(str[size]) == 0)
			break ;
		size--;
	}
	return (0);
}

// Checks for ><
int	redir_error(char *str)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(str);
	while (i < size - 1)
	{
		while (str[i] && str[i] != '<' && str[i] != '>' && str[i] != '\''
			&& str[i] != '\"')
			i++;
		if (str[i])
			i = skip_quotes(str, i);
		if (str[i] && str[i] == '>')
			if (str[++i] == '<')
				return (token_message(str[i]));
		i++;
	}
	return (0);
}

//Checks for << | and for >> |
int	double_redir_error(char *str, char c)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(str);
	while (i < size - 1)
	{
		while (i < size && str[i] != c && str[i] != '\'' && str[i] != '\"')
			i++;
		if (i < size)
			i = skip_quotes(str, i);
		i++;
		if (i < size && str[i] == c)
			i++;
		while (i < size && meta_char(str[i]) == 1)
			i++;
		if (i < size)
			i = skip_quotes(str, i);
		if (i < size && ((str[i] == '|' && str[i - 1] == '<') || \
			(meta_char(str[i]) == 2 && meta_char(str[i - 1]) == 1)))
				return (token_message(str[i]));
		i++;
	}
	return (0);
}

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
		while (str[i] && str[i] != '<' && str[i] != '>' && str[i] != '\''
			&& str[i] != '\"')
			i++;
		if (i < size)
			i = skip_quotes(str, i);
		i++;
		if (i < size && meta_char(str[i]) == 1)
			while (str[i] && meta_char(str[i]) == 1)
				i++;
		else
			i++;
		if (i < size)
			i = skip_quotes(str, i);
		if (i < size && meta_char(str[i]) == 2)
			return (token_message(str[i]));
		i++;
	}
	return (0);
}

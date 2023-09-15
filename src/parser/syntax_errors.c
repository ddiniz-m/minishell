/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:44:37 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/15 18:02:10 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	syntax_message(char c)
{
	printf("Syntax error: '%c'\n", c);
	return (1);
}

//Return 1 if c is a whitespace
int	is_whitespace(char c)
{
	if (c <= 20 || c == 127)
		return (1);
	return (0);
}

char	in_sucession(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] != '<' && str[i] != '>' && str[i] != '|')
			i++;
		i++;
		if (str[i] && is_whitespace(str[i]))
			while (str[i] && is_whitespace(str[i]))
				i++;
		else
			i++;
		if (str[i] && (str[i] == '<' || str[i] == '>' || str[i] == '|'))
			return (str[i]);
		i++;
	}
	return (0);
}

int	syntax_errors(char *str)
{
	if (!str)
		return (0);
	if (in_sucession(str))
	{
		return (syntax_message(in_sucession(str)));
	}
	return (0);
}
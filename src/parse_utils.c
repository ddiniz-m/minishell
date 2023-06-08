/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:31:51 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/07 16:56:221 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// how many words are in str
int	str_words(char *str)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '|'))
			i++;
		if (str[i])
			words++;
		while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '|')
			i++;
	}
	return (words);
}

// how man c are in str
// see if quotes are odd or even
int	n_char(char *str, char c)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (str[i])
	{
		if (str[i] == c)
			n++;
		i++;
	}
	return (n);
}

//unfinished and probably too messy
int	quote_state(char *str, char c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] != c)
			i++;
		if (str[i++] == c)
			j++;
		if (j == 2)
			return (1);
	}
	if (j == 1)
		return (2);
	return (0);
}
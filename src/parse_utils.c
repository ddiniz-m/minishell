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
	while(str && str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		if (str[i])
			words++;
		while(str[i] && str[i] != ' ' && str[i] != '\t')
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
	while(str[i++])
		if (str[i] == c)
			n++;
	return (n);
}

//unfinished and probably too messy
//wanted to make a function that did this:
// str = echo "a" " --> return (1) (there are 1 closed "". Return when it finds 2nd)
// str = echo 'a' " --> return (2) (there are 1 closed ''. Return when it finds 2nd)
// str = echo "a --> return (3) (there is 1 open " until the end of string)
// str = echo 'a --> return (4) (there is 1 open ' until the end of string)
int	quotes(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		while(str[i] != '\"' && str[i] != '\'')
			i++;
		if (str[i] != '\"')
			return (1);
		else
			return (2);
	}
	return (0);
}
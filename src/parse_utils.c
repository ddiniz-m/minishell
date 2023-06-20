/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:28:49 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/20 14:57:52 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	str_words_quotes(t_var *var, char *str, int i)
{
	if (str[i] == '\'')
	{
		i++;
		if (str[i] && meta_char(str[i]) != 1 && str[i] != '\'')
			var->words++;
		while (str[i] && str[i] != '\'')
			i++;
		i++;
	}
	else if (str[i] == '\"')
	{
		i++;
		if (str[i] && meta_char(str[i]) != 1 && str[i] != '\"')
			var->words++;
		while (str[i] && str[i] != '\"')
			i++;
		i++;
	}
	return (i);
}

// how many words are in str
void	str_words(t_var *var, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i = str_words_quotes(var, str, i);
		if (meta_char(str[i]) == 0)
		{
			var->words++;
			while (str[i] && meta_char(str[i]) == 0)
				i++;
		}
		else if (meta_char(str[i]) == 1)
		{
			while (str[i] && meta_char(str[i]) == 1)
				i++;
		}
		else if (meta_char(str[i]) == 2)
		{
			var->words++;
			while (str[i] && meta_char(str[i]) == 2)
				i++;
		}
	}
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

//Return 0 if regular char;
//Return 1 if space or tab;
//Return 2 if any other meta character;
int	meta_char(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	if (c == '$' || c == '>' || c == '<')
		return (2);
	if (c == '|' || c == '\\' || c == '.')
		return (2);
	return (0);
}

int	arr_size(char **arr)
{
	int	i;

	i = 0;
	if (!arr || !arr[i])
		return (0);
	while (arr[i])
		i++;
	return (i);
}

char	**arr_cpy(char **arr, int pos, int size)
{
	int		i;
	char	**buf;

	i = 0;
	buf = malloc(sizeof(buf) * (size + 1));
	if (!buf)
		return (NULL);
	while (i < size)
	{
		buf[i] = malloc(sizeof(char) * (ft_strlen(arr[pos]) + 1));
		ft_strlcpy(buf[i], arr[pos], ft_strlen(arr[pos]) + 1);
		i++;
		pos++;
	}
	return (buf);
}

void	arr_print(char *str, char **arr)
{
	int	i;

	i = 0;
	printf("\n%s:\n", str);
	while (i < arr_size(arr))
		printf("%s\n", arr[i++]);
}

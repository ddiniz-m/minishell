/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:02:32 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/08 18:15:25 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// size of str until next whitespace
int	split_word_len(char *str)
{
	int	i;

	i = 0;
	while(str[i] && (str[i] != ' ' || str[i] != '\t' || str[i] != '|'))
		i++;
	return (i);
}

char	*split_temp(char *str)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	temp = malloc(sizeof(char) * (split_word_len(str) + 1));
	if (!temp)
		return (NULL);
	while(temp[i])
		temp[i++] = *str++;
	temp[i] = '\0';
	return (temp);
}

char	**split(char *str)
{
	int	i;
	int		words;
	char	**buff;

	i = 0;
	words = str_words(str);
	buff = malloc(sizeof(char *) * (words + 1));
	if (!buff)
		return (NULL);
	while(i < words)
	{
		printf("test\n");
		while(*str && (*str == ' ' || *str == '\t' || *str == '|'))
			str++;
		buff[i++] = split_temp(str);
	}
	buff[i]= 0;
	return(buff);
}
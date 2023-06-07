/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:02:32 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/07 18:29:41 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//unfinished
char	*split_temp(char *str)
{
	int		i;
	char	*temp;

	i = 0;
	temp = malloc(sizeof(char) * (ft_strlen(str) + 1));
}

// size of str until next whitespace
int	split_word_len(char *str)
{
	int	i;

	i = 0;
	while(str[i] && (str[i] != ' ' || str[i] != '\t'))
		i++;
	return (i);
}	

//unfinished
char	**split(char *str)
{
	int		words;
	char	**buff;

	words = str_words(str);
	buff = malloc(sizeof(char *) * (words + 1));
	if (!buff)
		return (1);
	while(*str)
	{
		while(*str == ' ' || *str == '\t')
			str++;
	}
	return(buff);
}
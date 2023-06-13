/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:10:25 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/13 16:01:55 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//counts how many flags/words echo will use/print, beginning at echo's position
int	echo_n_words(char **arr, int pos, int words)
{
	int		i;

	i = 0;
	while (pos < words)
	{
		i++;
		pos++;
		if (arr[pos] && arr[pos][0] == '|')
			return (i);
	}
	return (i);
}

//creates an array with echo and its respective contents (flags and text)
char	**echo_join_words(char **arr, int words)
{
	int		i;
	int		pos;
	int		echo_words;
	char	**echo;

	pos = 0;
	while (pos < words)
	{
		if (ft_strncmp("echo", arr[pos], ft_strlen(arr[pos])) == 0)
			break ;
		pos++;
		if (pos == words)
			return (NULL);
	}
	echo_words = echo_n_words(arr, pos, words);
	echo = malloc(sizeof(char *) * (echo_words + 1));
	i = 0;
	while (i < echo_words)
	{
		echo[i] = malloc(sizeof(char) * (strlen(arr[pos])));
		ft_strlcpy(echo[i], arr[pos], ft_strlen(arr[pos]) + 1);
		i++;
		pos++;
	}
	echo[i] = 0;
	return (echo);
}
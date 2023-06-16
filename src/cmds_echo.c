/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:10:25 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/16 18:31:27 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//counts how many valid echo commands there are
int	echo_n(char **arr, int words)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (i < words)
	{
		if (arr[i] && ft_strncmp("echo", arr[i], ft_strlen(arr[i])) == 0)
			n++;
		while (arr[i] && meta_char(arr[i][0]) != 2)
			i++;
		i++;
	}
	return (n);
}

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
char	**echo_arr(char **arr, int words)
{
	int		i;
	int		pos;
	char	**echo;
	int		echo_size;

	pos = 0;
	while (pos < words)
	{
		if (ft_strncmp("echo", arr[pos], ft_strlen(arr[pos])) == 0)
			break ;
		pos++;
		if (pos == words)
			return (NULL);
	}
	echo_size = echo_n_words(arr, pos, words);
	echo = malloc(sizeof(char *) * (echo_size + 1));
	i = 0;
	while (i < echo_size)
	{
		echo[i] = malloc(sizeof(char) * (strlen(arr[pos])));
		ft_strlcpy(echo[i], arr[pos], ft_strlen(arr[pos]) + 1);
		i++;
		pos++;
	}
	echo[i] = 0;
	return (echo);
}


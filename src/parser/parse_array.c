/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:01:18 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/07/05 17:38:38 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	arr_size(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
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
	buf = ft_calloc((size + 1), sizeof(char *));
	if (!buf)
		return (NULL);
	while (i < size)
	{
		buf[i] = ft_calloc(ft_strlen(arr[pos] + 1), sizeof(char));
		buf[i] = arr[pos];
		i++;
		pos++;
	}
	return (buf);
}

void	arr_print(char *str, char **arr)
{
	int	i;

	i = 0;
	if (str)
		printf("\n%s:\n", str);
	while (arr[i] && i < arr_size(arr))
		printf("%s\n", arr[i++]);
}

void	arr_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] && i < arr_size(arr))
		free(arr[i++]);
	free(arr);
}

char	**arr_add(char **arr, char *str)
{
	int		i;
	int		size;
	char	**buf;

	i = 0;
	size = arr_size(arr);
	buf = ft_calloc(size + 2, sizeof(char *));
	while (i < size)
	{
		buf[i] = ft_calloc(ft_strlen(arr[i]), sizeof(char));
		buf[i] = arr[i];
		i++;
	}
	buf[i] = ft_calloc(ft_strlen(str), sizeof(char));
	buf[i] = str;
	return (buf);
}
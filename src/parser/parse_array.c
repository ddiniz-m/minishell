/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:01:18 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/12 18:28:36 by mortins-         ###   ########.fr       */
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
		buf[i] = ft_calloc((ft_strlen(arr[pos]) + 1), sizeof(char));
		ft_strlcpy(buf[i], arr[pos], ft_strlen(arr[pos]) + 1);
		i++;
		pos++;
	}
	return (buf);
}

void	arr_print(char *str, char **arr)
{
	int	i;
	int	j;

	i = 0;
	if (!arr)
		return ;
	j = arr_size(arr);
	printf("ARRAY SIZE = %d\n", j);
	printf("	%s:\n", str);
	while (arr[i] && i < j)
		printf("		%s\n", arr[i++]);
}

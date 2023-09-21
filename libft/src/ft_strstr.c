/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:11:59 by mira              #+#    #+#             */
/*   Updated: 2023/09/21 11:18:30 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (to_find[j] && str[i] == to_find[j])
		{
			i++;
			j++;
		}
		i++;
		if (to_find[j])
			return (str + (i - j - 1));
	}
	if (to_find[0])
		return (str - 1);
	return (0);
}

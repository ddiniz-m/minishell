/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:48:00 by mortins-          #+#    #+#             */
/*   Updated: 2023/10/17 10:12:41 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Returns length of string when it reaches c.
int	strlen_chr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

// Compares s1 and s2 until s2 reaches c, including c.
int	strcmp_chr(char *s1, char *s2, char c)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]) && i < strlen_chr(s2, c))
		i++;
	return (s1[i] - s2[i]);
}

char	*str_front_trim(char *str, char *trim)
{
	int		i;
	char	*buff;

	while (*str && ft_strchr(trim, *str))
		str++;
	i = ft_strlen(str) - 1;
	i++;
	buff = (char *)malloc(sizeof(char) * (i + 1));
	if (!buff)
		return (0);
	ft_strlcpy(buff, str, i + 1);
	return (buff);
}

// Compares s1 and s2 until s2 reaches c, excluding c.
// Since it excludes c, we have to make sure that we reached the end of s1,
// otherwise it shouldn't return 0.
int	strcmp_nochr(char *s1, char *s2, char c)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]) && i < strlen_chr(s2, c) - 1)
		i++;
	if (i < (int)ft_strlen(s1) - 1)
		return (1);
	return (s1[i] - s2[i]);
}

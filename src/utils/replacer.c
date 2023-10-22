/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:14:37 by mortins-          #+#    #+#             */
/*   Updated: 2023/10/22 17:41:29 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	skip_var(char *str, int pos)
{
	if (str[pos] == '$')
	{
		pos++;
		if (str[pos] && str[pos] >= 48 && str[pos] <= 57)
			pos++;
		else if (str[pos] && (ft_isalpha(str[pos]) || str[pos] == '_'))
		{
			pos++;
			while (str[pos] && (ft_isalnum(str[pos]) || str[pos] == '_'))
				pos++;
		}
	}
	return (pos);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:18:20 by mortins-          #+#    #+#             */
/*   Updated: 2023/05/19 16:30:05 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

//	Converts the letter 'c' to upper case, if possible

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

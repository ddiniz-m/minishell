/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:19:33 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/20 18:57:08 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// In the future this function will look through the separated string and
// interpret it before deciding what to do with it (i.e. what commands to
// execute, what to redirect, what to pipe, etc.)
void	parse_main(t_var *var)
{
	int	i;

	i = 0;
	arr_print("MAIN ARRAY", var->main_arr);
}

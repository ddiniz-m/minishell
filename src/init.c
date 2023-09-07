/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:12:34 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/07 17:33:02 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_minishell	*struct_init(void)
{
	t_minishell	*ms;

	ms = malloc(sizeof(t_minishell));
	ms->cmdtable = malloc(sizeof(t_cmdt));
	ms->cmdtable->content = malloc(sizeof(t_cont));
	return (ms);
}

void	init(t_minishell *ms)
{
	ms->words = 0;
	str_counter(ms, ms->str);
	ms->main_arr = split_main(ms, ms->str);
}

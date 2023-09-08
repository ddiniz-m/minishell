/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:59:22 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/08 17:54:30 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//	'readline' records whatever is inputed in terminal, and returns a memory
//	allocated char *buffer
int	main(void)
{
	t_minishell	*ms;

	ms = struct_init();
	signal_init();
	while (1)
	{
		ms->prompt = set_prompt(ms);
		ms->str = readline(ms->prompt);
		var_init(ms);
		parse_main(ms);
		add_history(ms->str);
		signal_exit(ms);
		free(ms->str);
		free(ms->prompt);
		free_array(ms->main_arr);
		free_cmd_list(ms->cmdlist);
	}
	free(ms->cmdlist);
	free(ms);
}

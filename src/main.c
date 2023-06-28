/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:59:22 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/06/28 16:42:23 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//	'readline' records whatever is inputed in terminal, and returns a memory
//	allocated char *buffer
int	main(int ac, char **av, char **env)
{
	t_var	*var;

	var = var_struct_init();
	signal_init();
	(void)ac;
	(void)av;
	while (1)
	{
		var->prompt = set_prompt(var);
		var->str = readline(var->prompt);
		var_init(var, env);
		parse_main(var);
		add_history(var->str);
		signal_exit(var);
		free(var->str);
		free(var->prompt);
		free_array(var->main_arr);
	}
	free(var);
}

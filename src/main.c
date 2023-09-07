/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:59:22 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/07 17:16:49 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//	'readline' records whatever is inputed in terminal, and returns a memory
//	allocated char *buffer
int	main(void)
{
	int		synt_err;
	t_var	*var;

	var = var_struct_init();
	signal_init();
	while (1)
	{
		var->prompt = set_prompt(var);
		var->str = readline(var->prompt);
		synt_err = syntax_error(var->str);
		if (!synt_err)
		{
			var_init(var);
			parse_main(var);
		}
		signal_exit(var);
		add_history(var->str);
		free(var->str);
		free(var->prompt);
		if (!synt_err)
			free_array(var->main_arr);
	}
	free(var);
}

/*	To do:
	- Figure out where/how we are gonna substitute ($VAR) by it's actual value

	Errors on:
	- str_quotes();

	Needs attention:
	- malloc_error();
	- pwd();
	- str_quotes();
	- syntax_error();
 */

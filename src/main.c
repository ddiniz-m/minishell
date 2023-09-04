/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:59:22 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/04 14:18:05 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//	'readline' records whatever is inputed in terminal, and returns a memory
//	allocated char *buffer
int	main(void)
{
	t_var	*var;

	var = var_struct_init();
	signal_init();
	while (1)
	{
		var->prompt = set_prompt(var);
		var->str = readline(var->prompt);
		var_init(var);
		parse_main(var);
		add_history(var->str);
		signal_exit(var);
		free(var->str);
		free(var->prompt);
		free_array(var->main_arr);
	}
	free(var);
}

/*	To do:
	- Figure out how to handle empty quotes
	- Maybe check for syntax errors before starting to parse <var>
	- Need a separate function to check if there are unclosed quote marks
	- Figure out where/how we are gonna substitute ($VAR) by it's actual value

	Errors on:
	- str_words();
	- split_quotes();
	- split_word();
	- str_words_quotes();

	Needs attention:
	- malloc_error();
	- pwd();
	- split_word();
	- str_words_quotes()
 */

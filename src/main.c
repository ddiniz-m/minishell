/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:59:22 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/13 11:15:40 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//	'readline' records whatever is inputed in terminal, and returns a memory
//	allocated char *buffer
int	main(void)
{
	t_minishell	*ms;

	ms = malloc(sizeof(t_minishell));
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

/*
	What if instead of always creating an array and then transforming it into a
	lst, we created a struct from the begining?
	We only need the array for execve so it would be easier and more productive. 
	If we only created an array from t_cmdlist before calling execve, we would 
	only create arrays when necessary, and we could free them after we used them.

	Response: Nah

	Fixed: `< test.txt < test2.txt echo 1 2 3 > test3 > test4 | <test5 <testa export a b c> test6 >testb`
		-fixed: when redirecting input, the program wouldn't see any commands after the redirect;
		-fixed: all input and output redirects were being added to each t_cmdlist node;
		-fixed: would break with multiple cmds with input/outputs
		-fixed: would break with multiple cmds with multiple input/outputs
	
	Need to correct:
		-cmd_count()
		-out_lst()
		-in_lst()
		-Weird behavior when the line after prompt gets longer than the terminal window
*/
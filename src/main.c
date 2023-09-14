/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:59:22 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/14 17:22:09 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//	'readline' records whatever is inputed in terminal, and returns a memory
//	allocated char *buffer
int	main(int ac, char **av, char **envp)
{
	t_minishell	*ms;

	ms = malloc(sizeof(t_minishell));
	signal_init();
	while (1)
	{
		ms->prompt = set_prompt(ms);
		ms->str = readline(ms->prompt);
		var_init(ms);
		exec(ms, envp);
		add_history(ms->str);
		signal_exit(ms);
		free(ms->str);
		free(ms->prompt);
		free_array(ms->main_arr);
		free_cmd_list(ms->cmdlist);
	}
	free(ms->cmdlist);
	free(ms);
	(void)ac;
	(void)av;
}
/*
	t_cmd	| t_content	content
			| int		last_in
			| int		last_out
			| t_cmd		next

	if last_in == 0
		no input
	if last_in == 1
		input redir '<'
	if last_in == 2
		input redir '<<'
	same for output
*/

/*
	What if instead of always creating an array and then transforming it into a
	lst, we created a struct from the begining?
	We only need the array for execve so it would be easier and more productive. 
	If we only created an array from t_cmdlist before calling execve, we would 
	only create arrays when necessary, and we could free them after we used them.

	`< test.txt < test2.txt cmd1 1 2 3 > test3 > test4 | <test5 <testa cmd2 a b c> test6 >testb`
	
	Need to correct:
		-out_lst()
		-in_lst()
		-content_init()
*/
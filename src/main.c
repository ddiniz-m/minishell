/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:59:22 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/10/03 15:14:07 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//	'readline' records whatever is inputed in terminal, and returns a memory
//	allocated char *buffer
int	main(int ac, char **av, char **envp)
{
	t_minishell	*ms;

	ms = malloc(sizeof(t_minishell));
	ms->env = env_init(envp);
	ms->exp = export_init(ms->env);
	signal_init();
	while (1)
	{
		ms->prompt = set_prompt(ms);
		ms->str = readline(ms->prompt);
		var_init(ms);
		parse_main(ms);
		run(ms);
		add_history(ms->str);
		signal_exit(ms);
		free(ms->str);
		free(ms->prompt);
		free_array(ms->main_arr);
		free_cmd_list(ms->cmdlist);
	}
	(void)av;
	(void)ac;
}
/*
	while (arr[i])
	{
		if (arr[i] == "<")
		{
			redir(buf, input);
			input = input->next;
		}
		else if (arr[i] == "<<")
		{
			redir(buf, heredoc);
			heredoc = heredoc->next;
		}
		i++
	}
*/

/*
	Need to figure out how we're actually gonna do heredoc
*/

// `>output>>append cmd1 1 2 3<input<<heredoc | <in<<here cmd2 a b c>out>>app`

/*	To do:
	- Check for syntax errors before starting to parse <var>
	- Figure out where/how we are gonna substitute ($VAR) by it's actual value

	Syntax Errors:
	- Unclosed quote marks
	- Some pipe behavior `||`; `| |`

	Errors on:
	- str_quotes();

	Needs attention:
	- malloc_error();
	- pwd();
	- str_quotes()
 */

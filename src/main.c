/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:59:22 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/19 15:18:00 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//	'readline' records whatever is inputed in terminal, and returns a memory
//	allocated char *buffer
int	main(int ac, char **av, char **envp)
{
	t_minishell	*ms;
	t_list		**env;
	t_list		**exp;

	env = env_init(envp);
	exp = export_init(env);
	ms = malloc(sizeof(t_minishell));
	signal_init();
	while (1)
	{
		ms->prompt = set_prompt(ms);
		ms->str = readline(ms->prompt);
		add_history(ms->str);
		if (ms->str && syntax_error(ms))
			continue ;
		var_init(ms);
		parse_main(ms->cmdlist, env, exp);
		signal_exit(ms);
		free(ms->str);
		free(ms->prompt);
		free_array(ms->main_arr);
		free_cmd_list(ms->cmdlist);
	}
	free_list(env);
	free_exp(exp);
	free(ms->cmdlist);
	free(ms);
	(void)ac;
	(void)av;
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

	<> works as <
	>| works as >
 */

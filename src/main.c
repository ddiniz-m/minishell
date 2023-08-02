/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:59:22 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/08/02 15:30:08 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//	'readline' records whatever is inputed in terminal, and returns a memory
//	allocated char *buffer
int	main(int ac, char **av, char **envp)
{
	t_var	*var;
	t_list	**env;
	t_list	**exp;

	env = env_init(envp);
	exp = export_init(env);
	var = var_struct_init();
	signal_init();
	while (1)
	{
		var->prompt = set_prompt(var);
		var->str = readline(var->prompt);
		var_init(var);
		parse_main(var, env, exp);
		add_history(var->str);
		signal_exit(var, env, exp);
		free(var->str);
		free(var->prompt);
	}
	free_var(var);
	free_list(env, 1);
	free_list(exp, 0);
	(void)ac;
	(void)av;
}

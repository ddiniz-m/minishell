/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:59:22 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/07/13 19:02:49 by mira             ###   ########.fr       */
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

	env = (t_list **)malloc(sizeof(env));
	exp =  (t_list **)malloc(sizeof(export));
	*env = NULL;
	*exp = NULL;
	env_init(env, envp);
	export_init(exp, env);
	var = var_struct_init();
	signal_init();
	while (1)
	{
		var->prompt = set_prompt(var);
		var->str = readline(var->prompt);
		var_init(var);
		parse_main(var, env, exp);
		add_history(var->str);
		signal_exit(var);
		free(var->str);
		free(var->prompt);
	}
	free_var(var);
	(void)ac;
	(void)av;
}

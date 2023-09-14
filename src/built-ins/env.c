/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 17:08:15 by mira              #+#    #+#             */
/*   Updated: 2023/08/02 14:30:35 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_list	**env_init(char **envp)
{
	int		i;
	t_list	*node;
	t_list	**env;

	i = 0;
	env = (t_list **)malloc(sizeof(env));
	*env = NULL;
	while (envp[i])
	{
		node = ft_lstnew(envp[i]);
		ft_lstadd_back(env, node);
		i++;
	}
	return (env);
}

//Checks if there is alredy str in env;
void	env_override(char *str, t_list **env)
{
	t_list	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (strcmp_chr(tmp->data, str, '=') == 0)
			ft_strcpy(tmp->data, str);
		tmp = tmp->next;
	}
}

int	env_check_dup(char *str, t_list **env)
{
	t_list	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strchr(str, '='))
			break ;
		if (strcmp_chr(tmp->data, str, '=') == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

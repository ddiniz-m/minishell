/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:40:31 by mortins-          #+#    #+#             */
/*   Updated: 2023/09/08 13:31:24 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*set_prompt(t_minishell *ms)
{
	char	cwd[PATH_MAX];
	char	*prompt;
	char	*buf;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		prompt = malloc(sizeof(char) * 25);
		if (!prompt)
			malloc_error(ms);
		prompt = "\033[1;33mMinishell $> \033[0m";
		return (prompt);
	}
	buf = ft_strjoin("\033[1;33m", ft_strrchr(getcwd(cwd, sizeof(cwd)), '/') \
		+ 1);
	if (!buf)
		malloc_error(ms);
	prompt = ft_strjoin(buf, " $> \033[0m");
	if (!prompt)
		malloc_error(ms);
	free(buf);
	return (prompt);
}

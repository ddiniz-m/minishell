/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:40:31 by mortins-          #+#    #+#             */
/*   Updated: 2023/06/22 19:06:16 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*set_prompt(void)
{
	char	cwd[PATH_MAX];
	char	*prompt;
	char	*buf2;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		prompt = malloc(sizeof(char) *14);
		if (!prompt)
			exit (1);
		prompt = "Minishell $> ";
		return (prompt);
	}
	buf2 = malloc(sizeof(char) * ft_strlen(ft_strrchr(getcwd(cwd, sizeof(cwd)), '/')));
	if (!buf2)
		exit (1);
	ft_strlcpy(buf2, ft_strrchr(getcwd(cwd, sizeof(cwd)), '/') + 1, ft_strlen(ft_strrchr(getcwd(cwd, sizeof(cwd)), '/')));
	prompt = ft_strjoin(buf2, " $> ");
	free(buf2);
	return (prompt);
}

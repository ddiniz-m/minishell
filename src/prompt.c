/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:40:31 by mortins-          #+#    #+#             */
/*   Updated: 2023/06/23 16:19:15 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*set_prompt(void)
{
	char	cwd[PATH_MAX];
	char	*prompt;
	char	*buf;
	char	*buf2;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		prompt = malloc(sizeof(char) *14);
		if (!prompt)
			exit (1);
		prompt = "Minishell $> ";
		return (prompt);
	}
	buf = malloc(sizeof(char) * ft_strlen(ft_strrchr(getcwd(cwd, sizeof(cwd)), '/')));
	if (!buf)
		exit (1);
	ft_strcpy(buf, ft_strrchr(getcwd(cwd, sizeof(cwd)), '/') + 1);
	buf2 = ft_strjoin("\033[1;33m", buf);
	free(buf);
	prompt = ft_strjoin(buf2, " $> \033[0m");
	free(buf2);
	return (prompt);
}

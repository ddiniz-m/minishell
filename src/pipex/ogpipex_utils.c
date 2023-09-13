/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:31:35 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/13 12:13:31 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**path_init(char **envp)
{
	int	i;
	char	**paths;
	char	*env_path;

	i = 0;
	while (ft_strnstr(*++envp, "PATH=", 5) == NULL)
		;
	env_path = ft_strtrim(*envp, "PATH=");
	paths = ft_split(env_path, ':');
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		i++;
	}
	free(env_path);
	return (paths);
}

char	*get_cmd(char *cmd, char **paths)
{
	int		i;
	char	*buf;

	i = 0;
	while ((paths)[i])
	{
		buf = ft_strjoin(paths[i], cmd);
		if (!access(buf, F_OK))
			return (buf);
		free(buf);
		i++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ogpipex_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:31:35 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/09/13 16:41:06 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**path_init(char **envp)
{
	int		i;
	char	**paths;
	char	*env_path;

	i = 0;
	while (ft_strnstr(*++envp, "PATH=", 5) == NULL)
		;
	env_path = ft_strtrim(*envp, "PATH=");
	paths = ft_split(env_path, ':');
	while (i++ < arr_size(paths))
		paths[i] = ft_strjoin(paths[i], "/");
	free(env_path);
	return (paths);
}

int	is_exec(char *str, char **paths)
{
	int		i;
	char	*buf;
	
	i = 0;
	while (paths[i])
	{
		buf = ft_strjoin(paths[i], str);
		if (!access(buf, F_OK))
			return (1);
		free(buf);
		i++;
	}
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:49:07 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/04/21 15:12:46 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**path_init(char **envp)
{
	char	**paths;
	char	*env_path;

	while (ft_strnstr(*++envp, "PATH=", 5) == NULL)
		;
	env_path = ft_strtrim(*envp, "PATH=");
	paths = ft_split2(env_path, ':');
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

void	close_all(t_pipex *pipex)
{
	if (pipex->pipefd[1] != -1)
		close(pipex->pipefd[1]);
	if (pipex->pipefd[0] != -1)
		close(pipex->pipefd[0]);
	if (pipex->fd_infile != -1)
		close(pipex->fd_infile);
	if (pipex->fd_outfile != -1)
		close(pipex->fd_outfile);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:03:09 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/04/24 13:53:34 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// opens infile and makes its fd, stdin
int	infile(t_pipex *pipex, char **av)
{
	pipex->fd_infile = open(av[1], O_RDONLY);
	if (pipex->fd_infile < 0)
	{
		perror(av[1]);
		return (1);
	}
	dup2(pipex->fd_infile, STDIN_FILENO);
	close(pipex->fd_infile);
	return (0);
}

// same as "child" in mandatory
int	child_process(char **av, int *fd, int arg, char **envp)
{
	char	*str;
	char	**paths;
	char	**buff;

	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	paths = path_init(envp);
	buff = ft_split(av[arg], ' ');
	str = get_cmd(buff[0], paths);
	free_arr(paths);
	if (!str || execve(str, buff, envp) == -1)
		perror(buff[0]);
	free(str);
	free_arr(buff);
	exit(0);
}

// creates pipe and forks process into a child and parent
void	pipe_fork(int *fd, char **av, int arg, char **envp)
{
	pid_t	child;

	if (pipe(fd) == -1)
	{
		perror("Pipe");
		exit(1);
	}
	child = fork();
	if (child == -1)
	{
		perror("Fork");
		exit(1);
	}
	if (child == 0)
		child_process(av, fd, arg, envp);
	else
	{
		close(fd[1]);
		wait(NULL);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}

// same as "parent" in mandatory. Only diference is that wait(), and some
//	dup2() and close() are in else in pipe_fork
int	outfile(t_pipex *pipex, char **av, int ac, char **envp)
{
	char	*str;
	char	**buff;
	char	**paths;

	pipex->fd_outfile = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->fd_outfile < 0)
	{
		perror("Outfile");
		return (1);
	}
	dup2(pipex->fd_outfile, STDOUT_FILENO);
	close(pipex->fd_outfile);
	paths = path_init(envp);
	buff = ft_split(av[ac - 2], ' ');
	str = get_cmd(buff[0], paths);
	free_arr(paths);
	if (!str || execve(str, buff, envp) == -1)
		perror(buff[0]);
	free(str);
	free_arr(buff);
	return (0);
}

//full process divided into 3 parts
// part 1: infile -> Only assigns stdin to infile.
// part 2: child_process -> In a while loop, creates child processes until
//	"arg" reaches the second to last cmd.
// part 3: outfile -> Same as mandatory "parent" (deals with last cmd and
//	 outfile)
int	main(int ac, char **av, char **envp)
{
	int		arg;
	int		fd[2];
	t_pipex	pipex;

	if (ac < 5)
		return (printf("Not enough arguments"));
	if (infile(&pipex, av) != 0)
		return (1);
	arg = 2;
	while (arg != ac - 2)
		pipe_fork(fd, av, arg++, envp);
	if (outfile(&pipex, av, ac, envp) != 0)
		return (1);
	return (0);
}

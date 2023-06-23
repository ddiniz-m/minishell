/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 13:49:48 by ddiniz-m          #+#    #+#             */
/*   Updated: 2023/04/24 13:42:15 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// deals with infile and command 1
// makes fd of infile, stdin, and fd[1] of pipe, stdout
// char *str = command path
// char **cmd = command and flags
void	child(t_pipex *pipex, char **envp, char **av)
{
	char	*str;
	char	**cmd;
	char	**paths;

	dup2(pipex->fd_infile, STDIN_FILENO);
	dup2(pipex->pipefd[1], STDOUT_FILENO);
	close_all(pipex);
	paths = path_init(envp);
	cmd = ft_split(av[2], ' ');
	str = get_cmd(cmd[0], paths);
	free_arr(paths);
	if (!str || execve(str, cmd, envp) == -1)
		perror("cmd1");
	free(str);
	free_arr(cmd);
	close_all(pipex);
	exit(1);
}

// wait for child process to finish
// deals with outfile and command 2
// makes fd[0] of pipe, stdin, and fd of outfile, stdout
void	parent(t_pipex *pipex, char **envp, char **av)
{
	char	*str;
	char	**cmd;
	char	**paths;

	wait(NULL);
	dup2(pipex->pipefd[0], STDIN_FILENO);
	dup2(pipex->fd_outfile, STDOUT_FILENO);
	close_all(pipex);
	paths = path_init(envp);
	cmd = ft_split(av[3], ' ');
	str = get_cmd(cmd[0], paths);
	free_arr(paths);
	if (!str || execve(str, cmd, envp) == -1)
		perror("cmd2");
	free(str);
	free_arr(cmd);
	close_all(pipex);
	exit (1);
}

//initializes pipe fds, and forks the process into two (each with its own pid)
//child process pid is 0 and parent is a positive number
void	pipe_x(t_pipex *pipex, char **envp, char **av)
{
	pid_t	pid;

	if (pipe(pipex->pipefd) == -1)
	{
		perror("Pipe");
		exit(1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Fork");
		exit(1);
	}
	if (pid == 0)
		child(pipex, envp, av);
	else
		parent(pipex, envp, av);
}

// open infile and outfile fds and deals with respective errors
//O_CREAT - creates file if it doesn't exit
//O_TRUNC - empties file if it exits
int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac != 5)
	{
		ft_printf("Incorret amount of arguments\n");
		return (0);
	}
	pipex.fd_infile = open(av[1], O_RDONLY);
	if (pipex.fd_infile < 0)
	{
		perror(av[1]);
		return (1);
	}
	pipex.fd_outfile = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex.fd_outfile < 0)
		return (1);
	pipe_x(&pipex, envp, av);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_in_processes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:05:16 by vjean             #+#    #+#             */
/*   Updated: 2022/11/09 16:29:53 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_child(t_data *data, char *cmd_path, char **cmd)
{
	int	err;

	close(data->pipe_fd[0]);
	dup2(data->pipe_fd[1], STDOUT_FILENO);
	close(data->pipe_fd[1]);
	err = execve(cmd_path, cmd, data->envp);
	if (err == -1)
		perror("Error: could not execute child process\n");
	exit (1);
}

void	execute_child2(t_data *data, char *cmd_path, char **cmd)
{
	int	err;

	close(data->pipe_fd[1]);
	dup2(data->pipe_fd[0], STDIN_FILENO);
	close(data->pipe_fd[0]);
	err = execve(cmd_path, cmd, data->envp);
	if (err == -1)
		perror("Error: could not execute child 2 process\n");
	exit (1);
}


// BELOW: execute_child
	// int		fd_in;

	// fd_in = open(data->av[1], O_RDONLY, 0777);
	// dup2(fd_in, 0);
	// dup2(data->pipe_fd[1], 1);
	// close(data->pipe_fd[0]);
	// close(data->pipe_fd[1]);
	// close(fd_in);
	// execve(cmd_path, cmd, data->envp);
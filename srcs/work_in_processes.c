/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_in_processes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:05:16 by vjean             #+#    #+#             */
/*   Updated: 2022/11/17 16:15:42 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_child(t_data *data)
{
	int	fd_in;

	fd_in = open(data->av[1], O_RDONLY, 0777);
	if (fd_in < 0)
	{
		write(2, "Error: file1: permission denied", 31);
		close(fd_in);
		close(data->pipe_fd[0]);
		close(data->pipe_fd[1]);
		free_dbl_ptr(data->paths);
		free_dbl_ptr(data->cmd);
		free(data);
		exit (0);
	}
	dup2(data->pipe_fd[1], STDOUT_FILENO);
	dup2(fd_in, STDIN_FILENO);
	close(data->pipe_fd[0]);
	close(fd_in);
	close(data->pipe_fd[1]);
	execve(data->cmd_path, data->cmd, data->envp);
	exit (0);
}

void	execute_child2(t_data *data)
{
	int	fd_out;

	fd_out = open(data->av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_out < 0)
	{
		write(2, "Error: file2: permission denied", 31);
		close(fd_out);
		close(data->pipe_fd[0]);
		close(data->pipe_fd[1]);
		free_dbl_ptr(data->paths);
		free_dbl_ptr(data->cmd);
		free(data);
		exit (0);
	}
	dup2(data->pipe_fd[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	close(fd_out);
	execve(data->cmd_path, data->cmd, data->envp);
	exit (0);
}

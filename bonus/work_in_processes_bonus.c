/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_in_processes_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:44:38 by vjean             #+#    #+#             */
/*   Updated: 2022/11/15 10:45:23 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_child(t_data *data, char *cmd_path, char **cmd)
{
	int	fd_in;

	fd_in = open(data->av[1], O_RDONLY, 0777);
	dup2(data->pipe_fd[1], STDOUT_FILENO);
	dup2(fd_in, STDIN_FILENO);
	close(data->pipe_fd[0]);
	close(fd_in);
	close(data->pipe_fd[1]);
	execve(cmd_path, cmd, data->envp);
	exit (0);
}

void	execute_child2(t_data *data, char *cmd_path, char **cmd)
{
	int	fd_out;

	fd_out = open(data->av[4], O_WRONLY | O_TRUNC, 0777);
	dup2(data->pipe_fd[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	close(fd_out);
	execve(cmd_path, cmd, data->envp);
	exit (0);
}
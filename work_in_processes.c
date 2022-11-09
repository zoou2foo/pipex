/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_in_processes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:05:16 by vjean             #+#    #+#             */
/*   Updated: 2022/11/09 09:42:51 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_child(t_data *data, char *cmd_path, char **cmd)
{
	int		fd_in;

	fd_in = open(data->av[1], O_RDONLY, 0777);
	dup2(fd_in, 0);
	dup2(data->pipe_fd[1], 1);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	close(fd_in);
	execve(cmd_path, cmd, data->envp);
}

void	execute_parent(t_data *data, char *cmd_path, char **cmd)
{
	int		fd_out;

	fd_out = open(data->av[4], O_WRONLY | O_CREAT, 0777);
	dup2(data->pipe_fd[0], 0);
	dup2(fd_out, 1);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	close(fd_out);
	execve(cmd_path, cmd, data->envp);
}

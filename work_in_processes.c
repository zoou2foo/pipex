/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_in_processes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:05:16 by vjean             #+#    #+#             */
/*   Updated: 2022/11/09 13:35:59 by vjean            ###   ########.fr       */
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
	//close(data->pipe_fd[1]);
	close(fd_in);
	if (execve(cmd_path, cmd, data->envp) != 0)
	{
		write(2, "Error: cannot execute command\n", 31);
		exit (0);
	}	
}

void	execute_parent(t_data *data, char *cmd_path, char **cmd)
{
	int		fd_out;

	fd_out = open(data->av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(fd_out, 1);
	dup2(data->pipe_fd[0], 0);
	//close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	close(fd_out);
	if (execve(cmd_path, cmd, data->envp) != 0)
	{
		write(2, "Error: cannot execute command\n", 31);
		exit (0);
	}
}

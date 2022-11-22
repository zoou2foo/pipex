/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_in_processes_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:44:38 by vjean             #+#    #+#             */
/*   Updated: 2022/11/22 08:41:38 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_child(t_data *data)
{
	int	fd_in;

	fd_in = open(data->av[1], O_RDONLY, 0777);
	if (fd_in < 0)
	{
		put_error_message(data);
		close(fd_in);
		close(data->pipe_fd[0]);
		close(data->pipe_fd[1]);
		free_dbl_ptr(data->paths);
		free_dbl_ptr(data->cmd);
		free(data);
		exit (1);
	}
	dup2(data->pipe_fd[1], STDOUT_FILENO);
	dup2(fd_in, STDIN_FILENO);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	close(fd_in);
	execve(data->cmd_path, data->cmd, data->envp);
	exit (1);
}

void	execute_child2(t_data *data, char *cmd_path, char **cmd)
{
	int	fd_out;

	fd_out = open(data->av[4], O_WRONLY | O_TRUNC, 0777);
	if (fd_out < 0)
	{
		put_error_message(data);
		close(fd_out);
		close(data->pipe_fd[0]);
		close(data->pipe_fd[1]);
		free_dbl_ptr(data->paths);
		free_dbl_ptr(data->cmd);
		free(data);
		exit (1);
	}
	dup2(data->pipe_fd[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	close(fd_out);
	execve(cmd_path, cmd, data->envp);
	exit (0);
}

void	put_error_message(t_data *data)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(data->av[1], 2);
	ft_putstr_fd(": something bad happened\n", 2);
}

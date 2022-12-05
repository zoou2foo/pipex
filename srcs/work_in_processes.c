/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_in_processes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:05:16 by vjean             #+#    #+#             */
/*   Updated: 2022/12/05 08:48:22 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_child(t_data *data)
{
	if (data->fd_in < 0)
	{
		put_error_message(data);
		close(data->fd_in);
		close(data->pipe_fd[0]);
		close(data->pipe_fd[1]);
		free(data->cmd_path);
		free_dbl_ptr(data->paths);
		free_dbl_ptr(data->cmd);
		free(data);
		exit (1);
	}
	dup2(data->pipe_fd[1], STDOUT_FILENO);
	dup2(data->fd_in, STDIN_FILENO);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	close(data->fd_in);
	execve(data->cmd_path, data->cmd, data->envp);
	exit (1);
}

void	execute_child2(t_data *data)
{
	if (data->fd_out < 0)
	{
		put_error_message(data);
		close(data->fd_out);
		close(data->pipe_fd[0]);
		close(data->pipe_fd[1]);
		free_dbl_ptr(data->paths);
		free_dbl_ptr(data->cmd);
		free(data);
		exit (1);
	}
	dup2(data->pipe_fd[0], STDIN_FILENO);
	dup2(data->fd_out, STDOUT_FILENO);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	close(data->fd_out);
	execve(data->cmd_path, data->cmd, data->envp);
	exit (1);
}

void	put_error_message(t_data *data)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(data->av[1], 2);
	ft_putstr_fd(": something bad happened\n", 2);
}

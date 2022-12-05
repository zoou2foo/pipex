/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:45:02 by vjean             #+#    #+#             */
/*   Updated: 2022/12/05 09:04:07 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(t_data *data)
{
	check_args(data);
	if (pipe(data->pipe_fd) == -1)
	{
		write(2, ERROR_PIPE, ft_strlen(ERROR_PIPE));
		exit (1);
	}
	data->pid1 = fork();
	if (data->pid1 == -1)
	{
		write(2, ERROR_PIPE, ft_strlen(ERROR_PIPE));
		exit (1);
	}
	if (data->pid1 == 0)
		child_process(data);
	data->pid2 = fork();
	if (data->pid2 == -1)
	{
		write(2, ERROR_PIPE, ft_strlen(ERROR_PIPE));
		exit (1);
	}
	if (data->pid2 == 0)
		child2_process(data);
	close_n_wait(data);
}

void	child_process(t_data *data)
{
	data->cmd = ft_split(data->av[2], ' ');
	data->cmd_path = find_cmd(data);
	if (!data->cmd_path)
	{
		write(2, ERROR_CMD, ft_strlen(ERROR_CMD));
		close(data->pipe_fd[0]);
		close(data->pipe_fd[1]);
		close(data->fd_in);
		close(data->fd_out);
		free_dbl_ptr(data->paths);
		free_dbl_ptr(data->cmd);
		free(data);
		exit (1);
	}
	execute_child(data);
}

void	child2_process(t_data *data)
{
	data->cmd = ft_split(data->av[3], ' ');
	data->cmd_path = find_cmd(data);
	if (data->cmd_path == NULL)
	{
		write(2, ERROR_CMD, ft_strlen(ERROR_CMD));
		close(open(data->av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777));
		close(data->pipe_fd[0]);
		close(data->pipe_fd[1]);
		close(data->fd_in);
		close(data->fd_out);
		free_dbl_ptr(data->paths);
		free_dbl_ptr(data->cmd);
		free(data);
		exit (1);
	}
	execute_child2(data);
}

void	close_n_wait(t_data *data)
{
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	waitpid(data->pid1, NULL, 0);
	waitpid(data->pid2, NULL, 0);
}

void	open_n_check(t_data *data)
{
	//data->fd_in = open(data->av[1], O_RDONLY, 0777);
	//data->fd_out = open(data->av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	check_args(data);
}
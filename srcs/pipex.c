/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:45:02 by vjean             #+#    #+#             */
/*   Updated: 2022/11/30 11:46:22 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(t_data *data)
{
	int	pid1;
	int	pid2;

	if (pipe(data->pipe_fd) == -1)
	{
		write(2, ERROR_PIPE, ft_strlen(ERROR_PIPE));
		exit (1);
	}
	pid1 = fork();
	if (pid1 == -1)
	{
		write(2, ERROR_PIPE, ft_strlen(ERROR_PIPE));
		exit (1);
	}
	if (pid1 == 0)
		child_process(data);
	pid2 = fork();
	if (pid2 == -1)
	{
		write(2, ERROR_PIPE, ft_strlen(ERROR_PIPE));
		exit (1);
	}
	if (pid2 == 0)
		child2_process(data);
	close_n_wait(data, pid1, pid2);
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
		free_dbl_ptr(data->paths);
		free_dbl_ptr(data->cmd);
		free(data);
		exit (1);
	}
	execute_child2(data);
}

void	close_n_wait(t_data *data, int pid1, int pid2)
{
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

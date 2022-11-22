/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:43:45 by vjean             #+#    #+#             */
/*   Updated: 2022/11/22 10:04:54 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// TODO will need a loop to make pipes = cmds - 1.
void	pipex(t_data *data)
{
	int	pid1;
	int	pid2;

	if (pipe(data->pipe_fd) == -1)
	{
		write(2, "Error: invalid pipe fd\n", 24);
		exit (1);
	}
	pid1 = fork();
	if (pid1 == -1)
	{
		write(2, "Error: invalid pipe fd\n", 24);
		exit (1);
	}
	else if (pid1 == 0)
		child_process(data);
	pid2 = fork();
	if (pid2 == -1)
	{
		write(2, "Error: invalid pipe fd\n", 24);
		exit (1);
	}
	else if (pid2 == 0)
		child2_process(data);
	close_n_wait(data, pid1, pid2);
}

void	child_process(t_data *data)
{
	data->cmd = ft_split(data->av[2], ' ');
	data->cmd_path = find_cmd(data);
	if (!data->cmd_path)
	{
		write(2, "Error: command does not exist\n", 39);
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
		write(2, "Error: command does not exist\n", 39);
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
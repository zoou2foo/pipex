/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:43:45 by vjean             #+#    #+#             */
/*   Updated: 2022/11/28 11:31:45 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	pipex(t_data *data)
{
	int	i;

	i = 0;
	if (pipe(data->pipe_fd) == -1)
	{
		write(2, "Error: invalid pipe fd\n", 24);
		exit (1);
	}
	while (i <= data->cmds_nb)
	{
		data->pid = fork();
		if (data->pid == -1)
		{
			write(2, "Error: invalid pipe fd\n", 24);
			exit (1);
		}
		else if (data->pid == 0)
			child_process(data, i);
		i++;
	}
	close_n_wait(data);
}

void	child_process(t_data *data, int index)
{
	int	i;

	if (data->flag_heredoc == 1)
		i = 3 + index;
	else
		i = 2 + index;
	// while (i < data->ac - 1) car déjà fait dans pipex
	data->cmd = ft_split(data->av[i], ' ');
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
	execute_child(data, i);
}

void	close_n_wait(t_data *data)
{
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	waitpid(data->pid, NULL, 0);
}

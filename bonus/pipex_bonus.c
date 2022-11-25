/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriejean <valeriejean@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:43:45 by vjean             #+#    #+#             */
/*   Updated: 2022/11/25 14:06:53 by valeriejean      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// TODO: one function that does 3 things at the same time: fork, redirect, exec
void	pipex(t_data *data)
{
	int	i;
	
	i = 0;
	if (pipe(data->pipe_fd) == -1)
 	{
 		write(2, "Error: invalid pipe fd\n", 24);
 		exit (1);
 	}
	if (data->flag_heredoc == 1)
	{
		while (i <= data->cmds_nb_w_heredoc)
		{
			data->pid = fork();
			if (data->pid == -1)
			{
				write(2, "Error: invalid pipe fd\n", 24);
				exit (1);
			}
			else if (data->pid == 0)
				child_process(data);
			i++;
		}
	}
	else
	{
		while (i <= data->cmds_nb)
		{
			data->pid = fork();
			if (data->pid == -1)
			{
				write(2, "Error: invalid pipe fd\n", 24);
				exit (1);
			}
			else if (data->pid == 0)
				child_process(data);
			i++;
		}
	}
	close_n_wait(data);
}

void	child_process(t_data *data)
{
	int	i;

	if (data->flag_heredoc == 1)
	{
		i = 3;
		while (i < data->ac - 1)
		{
			data->cmd = ft_split(data->av[i], ' ');
			data->cmd_path = find_cmd(data);
			if (!data->cmd_path)
			{
				write(2, "Error: command does not exist\n", 39);
				close(data->pipe_fd[0]);
				close(data->pipe_fd[1]);
				free_dbl_ptr(data->paths);
				free_dbl_ptr(data->cmd);
				free_dbl_ptr(data->gnl_return);
				free(data);
				exit (1);
			}
			execute_child(data);
			i++;
		}
	}
	else if (data->flag_heredoc == 0)
	{
		i = 2;
		while (i < data->ac - 1)
		{
			data->cmd = ft_split(data->av[i], ' ');
			data->cmd_path = find_cmd(data);
			if (!data->cmd_path)
			{
				write(2, "Error: command does not exist\n", 39);
				close(data->pipe_fd[0]);
				close(data->pipe_fd[1]);
				free_dbl_ptr(data->paths);
				free_dbl_ptr(data->cmd);
				free_dbl_ptr(data->gnl_return);
				free(data);
				exit (1);
			}
			execute_child(data);
			i++;
		}
	}
}

void	close_n_wait(t_data *data)
{
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	waitpid(data->pid, NULL, 0);
}
// ! probably need a while loop to waitpid ALL the pid. I need to check that
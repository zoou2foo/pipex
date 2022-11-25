/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriejean <valeriejean@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:43:45 by vjean             #+#    #+#             */
/*   Updated: 2022/11/25 11:29:24 by valeriejean      ###   ########.fr       */
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
			child_process(data);
			i++;
		}
	}
	else
	{
		while (i <= data->cmds_nb)
		{
			
			i++;
		}
	}
}
// ! Je dois probablement envoyer dans child_process dans la boucle
// ! Pour chaque fork d'effectuer... Pour que chaque enfant a ses
// ! pipe attribués. fork() dans le while

// {
// 	int	pid1;
// 	int	pid2;

// 	if (pipe(data->pipe_fd) == -1)
// 	{
// 		write(2, "Error: invalid pipe fd\n", 24);
// 		exit (1);
// 	}
// 	pid1 = fork();
// 	if (pid1 == -1)
// 	{
// 		write(2, "Error: invalid pipe fd\n", 24);
// 		exit (1);
// 	}
// 	else if (pid1 == 0)
// 		child_process(data);
// 	pid2 = fork();
// 	if (pid2 == -1)
// 	{
// 		write(2, "Error: invalid pipe fd\n", 24);
// 		exit (1);
// 	}
// 	else if (pid2 == 0)
// 		child2_process(data);
// 	close_n_wait(data, pid1, pid2);
// }

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
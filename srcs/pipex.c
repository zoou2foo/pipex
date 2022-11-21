/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:45:02 by vjean             #+#    #+#             */
/*   Updated: 2022/11/21 12:09:54 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	if (pid1 == 0)
		child_process(data);
	// waitpid(pid1, NULL, WNOHANG);
	pid2 = fork();
	if (pid2 == -1)
	{
		write(2, "Error: invalid pipe fd\n", 24);
		exit (1);
	}
	if (pid2 == 0)
		child2_process(data);
	// waitpid(pid2, NULL, WNOHANG);
	
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
}

void	child_process(t_data *data)
{
	// if (check_files(data, 1) == 1)
	// {
	// 	write(2, "Error: file does not exist (child1)\n", 37);
	// 	exit (0);
	// }
	data->cmd = ft_split(data->av[2], ' ');
	data->cmd_path = find_cmd(data);
	if (!data->cmd_path)
	{
		write(2, "Error: command does not exist(child1)\n", 39);
		close(data->pipe_fd[0]);
		close(data->pipe_fd[1]);
		exit (1);
	}
	execute_child(data);
}

void	child2_process(t_data *data)
{
	//int		fd_out;

	// fd_out = open(data->av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	// if (check_files(data, 4) == 1)
	// {
	// 	write(2, "Error: file does not exist (in child2)\n", 40);
	// 	exit (0);
	// }
	// close(fd_out);
	data->cmd = ft_split(data->av[3], ' ');
	data->cmd_path = find_cmd(data);
	if (data->cmd_path == NULL)
	{
		write(2, "Error: command does not exist(child2)\n", 39);
		close(data->pipe_fd[0]);
		close(data->pipe_fd[1]);
		exit (1);
	}
	execute_child2(data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:45:02 by vjean             #+#    #+#             */
/*   Updated: 2022/11/09 16:31:24 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// TODO free stuff in exit for function pipex
void	pipex(t_data *data)
{
	int	pipe_fd[2];
	int	pid1;
	int	pid2;

	data->pipe_fd = pipe_fd;
	if (pipe(pipe_fd) == -1)
	{
		write(2, "Error: invalid pipe fd\n", 24);
		exit (0);
	}
	pid1 = fork();
	if (pid1 == -1)
	{
		write(2, "Error: invalid pipe fd\n", 24);
		exit (0);
	}
	else if (pid1 == 0)
		child_process(data);
	pid2 = fork();
	if (pid2 == -1)
	{
		write(2, "Error: invalid pipe fd\n", 24);
		exit (0);
	}
	else if (pid2 == 0)
		child2_process(data);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	wait(&pid1);
	wait(&pid2);
}

// child_process takes filein and cmd1
// TODO free stuff in exit for function child_process
void	child_process(t_data *data)
{
	char	*cmd_path;
	char	**cmd;

	if (check_files(data, 1) == 1)
	{
		write(2, "Error: file does not exist (child1)\n", 32);
		exit (0);
	}
	cmd = ft_split(data->av[2], ' ');
	cmd_path = find_cmd(data, 2, cmd[0]);
	if (!cmd_path)
	{
		write(2, "Error: command does not exist(child1)\n", 38);
		exit (0);
	}
	execute_child(data, cmd_path, cmd);
}

// parent_process takes cmd2 and fileout
// TODO free stuff in exit for function pipex
void	child2_process(t_data *data)
{
	char	*cmd_path;
	char	**cmd;

	if (check_files(data, 4) == 1)
	{
		write(2, "Error: file does not exist (in)\n", 32);
		exit (0);
	}
	cmd = ft_split(data->av[3], ' ');
	cmd_path = find_cmd(data, 3, cmd[0]);
	printf("Child2: %s\n", cmd_path);
	if (cmd_path == NULL)
	{
		write(2, "Error: command does not exist(child2)\n", 38);
		exit (0);
	}
	execute_child2(data, cmd_path, cmd);
}

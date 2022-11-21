/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:43:45 by vjean             #+#    #+#             */
/*   Updated: 2022/11/15 13:21:06 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// TODO will need a loop to make pipes = cmds - 1.
void	pipex(t_data *data)
{
	int	pid1;
	int	pid2;

	if (pipe(data->pipe_fd) == -1)
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
}

void	child_process(t_data *data)
{
	char	*cmd_path;
	char	**cmd;

	if (check_files(data, 1) == 1)
	{
		write(2, "Error: file does not exist (child1)\n", 37);
		exit (0);
	}
	cmd = ft_split(data->av[2], ' ');
	cmd_path = find_cmd(data, cmd[0]);
	if (!cmd_path)
	{
		write(2, "Error: command does not exist(child1)\n", 39);
		exit (0);
	}
	execute_child(data, cmd_path, cmd);
}

void	child2_process(t_data *data)
{
	char	*cmd_path;
	char	**cmd;
	int		fd_out;

	fd_out = open(data->av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (check_files(data, 4) == 1)
	{
		write(2, "Error: file does not exist (in child2)\n", 40);
		exit (0);
	}
	close(fd_out);
	cmd = ft_split(data->av[3], ' ');
	cmd_path = find_cmd(data, cmd[0]);
	printf("Child2: %s\n", cmd_path);
	if (cmd_path == NULL)
	{
		write(2, "Error: command does not exist(child2)\n", 39);
		exit (0);
	}
	execute_child2(data, cmd_path, cmd);
}
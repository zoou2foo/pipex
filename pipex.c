/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:45:02 by vjean             #+#    #+#             */
/*   Updated: 2022/11/10 15:38:25 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(t_data *data)
{
	int	pipe_fd[2];
	int	pid1;
	int	pid2;

	data->pipe_fd = pipe_fd;
	if (pipe(pipe_fd) == -1)
	{
		write(2, "Error: invalid pipe fd\n", 24);
		free_all_tab(data);
		exit (0);
	}
	pid1 = fork();
	if (pid1 == -1)
	{
		write(2, "Error: invalid pipe fd\n", 24);
		free_all_tab(data);
		exit (0);
	}
	else if (pid1 == 0)
		child_process(data);
	pid2 = fork();
	if (pid2 == -1)
	{
		write(2, "Error: invalid pipe fd\n", 24);
		free_all_tab(data);
		exit (0);
	}
	else if (pid2 == 0)
		child2_process(data);
	free_all_tab(data);
	free(data);
}

void	child_process(t_data *data)
{
	char	*cmd_path;
	char	**cmd;

	if (check_files(data, 1) == 1)
	{
		write(2, "Error: file does not exist (child1)\n", 37);
		free_all_tab(data);
		free(data);
		exit (0);
	}
	cmd = ft_split(data->av[2], ' ');
	cmd_path = find_cmd(data, 2, cmd[0]);
	if (!cmd_path)
	{
		write(2, "Error: command does not exist(child1)\n", 39);
		free_all_tab(data);
		free(data);
		exit (0);
	}
	execute_child(data, cmd_path, cmd);
}

void	child2_process(t_data *data)
{
	char	*cmd_path;
	char	**cmd;

	if (check_files(data, 4) == 1)
	{
		write(2, "Error: file does not exist (in child2)\n", 40);
		free_all_tab(data);
		free(data);
		exit (0);
	}
	cmd = ft_split(data->av[3], ' ');
	cmd_path = find_cmd(data, 3, cmd[0]);
	printf("Child2: %s\n", cmd_path);
	if (cmd_path == NULL)
	{
		write(2, "Error: command does not exist(child2)\n", 39);
		free_all_tab(data);
		free(data);
		exit (0);
	}
	execute_child2(data, cmd_path, cmd);
}

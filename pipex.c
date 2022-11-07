/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:45:02 by vjean             #+#    #+#             */
/*   Updated: 2022/11/07 13:16:15 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(t_data *data)
{
	int		pipe_fd[2];
	int		pid1;

	if (pipe(pipe_fd) == -1)
	{
		write(2, "Error: invalid pipe fd\n", 23);
		exit ; // ! will need to free...
	}
	pid1 = fork();
	if (pid1 == -1)
	{
		write(2, "Error with the fork function\n", 29);
		exit ; // ! will need to free...
	}
	else if (pid1 == 0)
		child_process(data, pipe_fd);
	waitpid(pid1, NULL, 0);
	parent_process(data, pipe_fd);
}

// child_process takes filein and cmd1
void	child_process(t_data *data, int pipe_fd)
{
	char	*cmd;
	
	if (check_files(data->av[1]) == 1)
	{
		write(2, "Error: file does not exist (in)\n", 32);
		exit ; // ! will need to free stuff...
	}
	cmd = find_cmd(data, 2);
	if (cmd == NULL)
	{
		write(2, "Error: command does not exist(parent)\n", 38);
		exit ; // ! will need to free stuff...
	}
	execute_child(cmd, data);
}

// parent_process takes cmd2 and fileout
void	parent_process(t_data *data, int pipe_fd)
{
	char	*cmd;

	if (check_files(data->av[4]) == 1)
	{
		write(2, "Error: file does not exist (in)\n", 32);
		exit ; // ! will need to free stuff...
	}
	cmd = find_cmd(data, 3);
	if (cmd == NULL)
	{
		write(2, "Error: command does not exist(parent)\n", 38);
		exit ; // ! will need to free stuff...
	}
	execute_parent(data, cmd);
}
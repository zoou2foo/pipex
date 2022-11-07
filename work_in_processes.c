/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_in_processes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:05:16 by vjean             #+#    #+#             */
/*   Updated: 2022/11/07 15:51:53 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_child(t_data *data, char *cmd)
{
	int		fd_in;
	int		fd_out;
	char	**option;

	fd_in = open()
	fd_out = open()
	option = ft_split(data->av[2], ' ');
	dup2(fd_in, 0);
	dup2(data->pipe_fd[1], 1);
	printf("madafakas\n");
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	execve(cmd, option, data->envp);
}

void	execute_parent(t_data *data, char *cmd)
{
	int		fd_in;
	int		fd_out;
	char	**option;

	fd_in = 3;
	fd_out = 4;
	option = ft_split(data->av[3], ' ');
	dup2(data->pipe_fd[0], 0);
	dup2(fd_out, 1);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	execve(cmd, option, data->envp);
}

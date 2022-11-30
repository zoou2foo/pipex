/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:43:45 by vjean             #+#    #+#             */
/*   Updated: 2022/11/30 11:45:03 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	pipex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->cmds_nb)
	{
		pipe_error(data);
		if (data->pid > 0)
		{
			dup2(data->pipe_fd[0], STDIN_FILENO);
			close(data->pipe_fd[0]);
			close(data->pipe_fd[1]);
		}
		else if (data->pid == 0)
			child_process(data, i);
		i++;
	}
	close_n_wait(data);
}
// il faut dup2(data-pipe[0], STDIN_FILENO) et close les fd dans le parent
// sinon l'enfant n'a pas l'info d'où prendre son information pour lire
// Cela permet la connexion entre les enfants.
// le parent dit à l'enfant où lire, puis l'enfant écrit au parent, puis le
// parent dit à l'enfant où lire... ainsi de suite.

void	child_process(t_data *data, int index)
{
	int	i;

	if (data->flag_heredoc == 1)
		i = 3 + index;
	else
		i = 2 + index;
	data->cmd = ft_split(data->av[i], ' ');
	if (data->cmd_path)
		free(data->cmd_path);
	data->cmd_path = find_cmd(data);
	if (!data->cmd_path)
	{
		write(2, ERROR_CMD, ft_strlen(ERROR_CMD));
		close(data->pipe_fd[0]);
		close(data->pipe_fd[1]);
		free_dbl_ptr(data->paths);
		free_dbl_ptr(data->cmd);
		free(data);
		exit (1);
	}
	execute_child(data, index);
}

// ^ après le premier if else.  while (i < data->ac - 1) car déjà 
// fait dans pipex

void	close_n_wait(t_data *data)
{
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	waitpid(data->pid, NULL, 0);
}

void	pipe_error(t_data *data)
{
	if (pipe(data->pipe_fd) == -1)
	{
		write(2, ERROR_PIPE, ft_strlen(ERROR_PIPE));
		exit (1);
	}
	data->pid = fork();
	if (data->pid == -1)
	{
		write(2, ERROR_PIPE, ft_strlen(ERROR_PIPE));
		exit (1);
	}
}
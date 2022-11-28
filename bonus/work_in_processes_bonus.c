/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_in_processes_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:44:38 by vjean             #+#    #+#             */
/*   Updated: 2022/11/28 11:30:48 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// ? gérer quand arrêter avant fileout (donc dernière commande)
// ? si pas here_doc, ouvrir fd_in
// si i = nb de cmd, redirige STDOUT pas dans le pipe

void	execute_child(t_data *data, int index)
{
	int	fd_out;

	fd_out = open(data->av[data->ac], O_WRONLY | O_TRUNC, 0777);
	if (fd_out < 0)
	{
		put_error_message(data);
		close(fd_out);
		close(data->pipe_fd[0]);
		close(data->pipe_fd[1]);
		free_dbl_ptr(data->paths);
		free_dbl_ptr(data->cmd);
		free(data);
		exit (1);
	}
	if (index == data->cmds_nb)
	{
		dup2(data->pipe_fd[1], STDOUT_FILENO);
		close(data->pipe_fd[1]);
		close(data->pipe_fd[0]);
		close(fd_out);
		execve(data->cmd_path, data->cmd, data->envp);
		exit (1);
	}
	else
	{
		
	}
	
}

void	put_error_message(t_data *data)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(data->av[1], 2);
	ft_putstr_fd(": something bad happened\n", 2);
}

// {
// 	int	fd_in;

// 	fd_in = open(data->av[1], O_RDONLY, 0777);
// 	if (fd_in < 0)
// 	{
// 		put_error_message(data);
// 		close(fd_in);
// 		close(data->pipe_fd[0]);
// 		close(data->pipe_fd[1]);
// 		free_dbl_ptr(data->paths);
// 		free_dbl_ptr(data->cmd);
// 		free(data);
// 		exit (1);
// 	}
// 	dup2(data->pipe_fd[1], STDOUT_FILENO);
// 	dup2(fd_in, STDIN_FILENO);
// 	close(data->pipe_fd[0]);
// 	close(data->pipe_fd[1]);
// 	close(fd_in);
// 	execve(data->cmd_path, data->cmd, data->envp);
// 	exit (1);
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_in_processes_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:44:38 by vjean             #+#    #+#             */
/*   Updated: 2022/11/30 14:58:41 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute_child(t_data *data, int index)
{
	int	fd_out;

	if (index == data->cmds_nb - 1)
	{
		if (data->flag_heredoc == 1)
			fd_out = open(data->av[data->ac - 1], O_WRONLY | O_CREAT
					| O_APPEND, 0777);
		else
			fd_out = open(data->av[data->ac - 1], O_WRONLY | O_CREAT
					| O_TRUNC, 0777);
		if (fd_out < 0)
			error_n_free(data, fd_out, index);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	else
		dup2(data->pipe_fd[1], STDOUT_FILENO);
	close(data->pipe_fd[1]);
	close(data->pipe_fd[0]);
	execve(data->cmd_path, data->cmd, data->envp);
	exit (1);
}

void	put_error_message(t_data *data, int index)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(data->av[index], 2);
	ft_putstr_fd(": something bad happened\n", 2);
}

void	error_n_free(t_data *data, int fd_out, int index)
{
	put_error_message(data, index);
	close(fd_out);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	free_dbl_ptr(data->paths);
	free_dbl_ptr(data->cmd);
	free(data);
	exit (1);
}

// DRY: don't repeat yourself. Pour que ta fonction fasse une chose. Ex: 2 fois
// execve dans execute child dans mon if et else. Alors, peu importe, le
// outcome, il va execve anyway at the end. Alors, on sort la partie similaire
// pour mettre à la fin.
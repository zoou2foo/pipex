/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_in_processes_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:44:38 by vjean             #+#    #+#             */
/*   Updated: 2022/12/07 09:06:54 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute_child(t_data *data, int index)
{
	if (index == data->cmds_nb - 1)
	{
		dup2(data->fd_out, STDOUT_FILENO);
		close(data->fd_out);
	}
	else
		dup2(data->pipe_fd[1], STDOUT_FILENO);
	close(data->pipe_fd[1]);
	close(data->pipe_fd[0]);
	close(data->fd_out);
	execve(data->cmd_path, data->cmd, data->envp);
	exit (1);
}

void	put_error_message(t_data *data, int index)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(data->av[index], 2);
	ft_putstr_fd(": something bad happened\n", 2);
}

void	error_n_free(t_data *data, int index)
{
	put_error_message(data, index);
	close(data->fd_out);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	free_dbl_ptr(data->paths);
	free_dbl_ptr(data->cmd);
	free(data);
	exit (1);
}

void	check_args(t_data *data, int i)
{
	if (ft_strlen(data->av[i]) == 0)
	{
		write(2, NO_CMD, ft_strlen(NO_CMD));
		write(2, "\n", 1);
		check_args_close_n_free(data);
	}
	if (ft_strncmp(data->av[i], " ", 1) == 0)
	{
		write(2, NO_CMD, ft_strlen(NO_CMD));
		write(2, "\n", 1);
		check_args_close_n_free(data);
	}
}

void	check_args_close_n_free(t_data *data)
{
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	close(data->fd_in);
	close(data->fd_out);
	free_dbl_ptr(data->paths);
	free_dbl_ptr(data->cmd);
	free(data);
	exit (1);
}
// DRY: don't repeat yourself. Pour que ta fonction fasse une chose. Ex: 2 fois
// execve dans execute child dans mon if et else. Alors, peu importe, le
// outcome, il va execve anyway at the end. Alors, on sort la partie similaire
// pour mettre à la fin.
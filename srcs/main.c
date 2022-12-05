/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 11:33:23 by vjean             #+#    #+#             */
/*   Updated: 2022/12/05 09:05:20 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	data = ft_calloc(sizeof(t_data), 1);
	if (ac == 5)
	{
		init_struct(ac, av, envp, data);
		data->fd_in = open(data->av[1], O_RDONLY, 0777);
		data->fd_out = open(data->av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		fill_tab_env(data);
		pipex(data);
	}
	else
	{
		write(2, "Error: not enough arguments or too many\n", 41);
		exit (1);
	}
	close(data->fd_in);
	close(data->fd_out);
	free_dbl_ptr(data->paths);
	free_dbl_ptr(data->cmd);
	free(data);
	return (0);
}

void	check_args(t_data *data)
{
	if ((ft_strlen(data->av[2]) == 0) || (ft_strlen(data->av[3]) == 0))
	{
		write(2, NO_CMD, ft_strlen(NO_CMD));
		close(data->pipe_fd[0]);
		close(data->pipe_fd[1]);
		close(data->fd_in);
		close(data->fd_out);
		free_dbl_ptr(data->paths);
		free_dbl_ptr(data->cmd);
		free(data);
		exit (1);
	}
	if ((ft_strncmp(data->av[2], " ", 1) == 0)
		|| (ft_strncmp(data->av[3], " ", 1) == 0))
	{
		write(2, NO_CMD, ft_strlen(NO_CMD));
		close(data->pipe_fd[0]);
		close(data->pipe_fd[1]);
		close(data->fd_in);
		close(data->fd_out);
		free_dbl_ptr(data->paths);
		free_dbl_ptr(data->cmd);
		free(data);
		exit (1);
	}
}

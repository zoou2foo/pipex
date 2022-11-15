/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:46:07 by vjean             #+#    #+#             */
/*   Updated: 2022/11/15 10:46:28 by vjean            ###   ########.fr       */
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
		if ((check_fds(data) == 1))
		{
			fill_tab_env(data);
			pipex(data);
		}
		else
			write(2, "Error: permission denied for file", 34);
	}
	else
		write(2, "Error: not enough arguments\n", 28);
	close (data->pipe_fd[0]);
	close (data->pipe_fd[1]);
	free_dbl_ptr(data->paths);
	free(data);
	return (0);
}

int	check_fds(t_data *data)
{
	int	fd_1;
	int	fd_2;

	fd_1 = open(data->av[1], O_RDONLY);
	fd_2 = open(data->av[4], O_WRONLY);
	if (fd_1 < 0)
		return (0);
	if (fd_2 < 0)
		return (0);
	return (1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 11:33:23 by vjean             #+#    #+#             */
/*   Updated: 2022/11/16 16:07:19 by vjean            ###   ########.fr       */
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
		fill_tab_env(data);
		pipex(data);
		// if ((check_fds(data) == 1))
		// {
		// }
		// else
		// 	write(2, "Error: permission denied for file", 34);
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

// besoin de revoir mon pipex, car si fichier1 ou cmd1 n'existe pas, il faut
// qu'il effectue quand même la cmd2 dans fichier2. Surtout si cmd2 existe.
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 11:33:23 by vjean             #+#    #+#             */
/*   Updated: 2022/11/14 15:04:04 by vjean            ###   ########.fr       */
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
	}
	else
		write(2, "Error: not enough arguments\n", 28);
	close (data->pipe_fd[0]);
	close (data->pipe_fd[1]);
	free_dbl_ptr(data->paths);
	free(data);
	return (0);
}

/*
Need to add in the if access for the file1 but not sure that I should check 
file2 as I have to create it
*/
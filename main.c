/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 11:33:23 by vjean             #+#    #+#             */
/*   Updated: 2022/11/10 15:12:20 by vjean            ###   ########.fr       */
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
	free(data);
	return (0);
}

// ! Ajouter les protections à ce que j'ai fait so far. Free des trucs

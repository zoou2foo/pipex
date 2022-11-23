/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:46:07 by vjean             #+#    #+#             */
/*   Updated: 2022/11/23 09:25:31 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"


// here_doca 
// here_doc
// 12345678
int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	data = ft_calloc(sizeof(t_data), 1);
	if (ac >= 5)
	{
		init_struct(ac, av, envp, data);
		if (ft_strncmp(data->av[1], "here_doc", ft_strlen(data->av[1])) == 0)
			here_doc(data);
		else
		{
			fill_tab_env(data);
			pipex(data);
		}	
	}
	else
	{
		write(2, "Error: not enough arguments\n", 28);
		exit (1);
	}
	free_dbl_ptr(data->paths);
	free_dbl_ptr(data->cmd);
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

void	here_doc(t_data *data)
{
	char	*gnl_return;

	while (1)
	{
		gnl_return = gnl_pipex();
		if ((ft_strncmp(gnl_return, data->av[2], ft_strlen(gnl_return) - 1))
			== 0)
			break ;
	}
}

char	*gnl_pipex(void)
{
	char	buffer[10000];
	int		size;

	size = read(1, buffer, 10000);
	buffer[size] = '\0';
	return (ft_strdup(buffer));
}

/*
il faut que je prenne le buffer pour rediriger dans le STDIN.
Puis, continuer. Ne pas oublier de faire un while pour pipe et fork.
pipe = cmds - 1;
nombre de cmds = entre av[2] et av[last] (excluant 2 et last)
*/

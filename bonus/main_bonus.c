/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:46:07 by vjean             #+#    #+#             */
/*   Updated: 2022/11/16 15:33:07 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	data = ft_calloc(sizeof(t_data), 1);
	if (ac >= 5)
	{
		init_struct(ac, av, envp, data);
		if (ft_strncmp(data->av[1], "here_doc", 8) == 0)
			here_doc(data);
		else
		{
			if ((check_fds(data) == 1))
			{
				fill_tab_env(data);
				pipex(data);
			}
			else
				write(2, "Error: permission denied for file", 34);
		}	
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

void	here_doc(t_data *data)
{
	char	*gnl_return;

	while (1)
	{
		gnl_return = gnl_pipex();
		if ((ft_strncmp(gnl_return, data->av[1], ft_strlen(gnl_return))) == 0)
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
To implement here_doc: it will be one of the args (in fact, av[1]). I need
to check if av[1] = here_doc; if yes, then I send it to a function to deal with
it. I'll need to use get_next_line. 
AND I send send multiple commands to my here_doc as it's the bonus.
Double check the pdf of pipex (code quoi)
*/
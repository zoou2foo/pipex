/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:46:07 by vjean             #+#    #+#             */
/*   Updated: 2022/11/23 08:24:26 by vjean            ###   ########.fr       */
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
		if (ft_strncmp(data->av[1], "here_doc", 8) == 0) //better to use ft_strlen than just put a random number?
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
To implement here_doc: it will be one of the args (in fact, av[1]). I need
to check if av[1] = here_doc; if yes, then I send it to a function to deal with
it. I'll need to use get_next_line. 
AND I send send multiple commands to my here_doc as it's the bonus.
Double check the pdf of pipex (code quoi)
*/
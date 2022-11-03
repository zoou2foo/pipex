/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriejean <valeriejean@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 08:05:05 by valeriejean       #+#    #+#             */
/*   Updated: 2022/11/03 09:25:47 by valeriejean      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	find_path(t_data *data)
{
	fill_tab_env(data);
}

void	fill_tab_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], "PATH=", 5) == 0)
		{
			data->paths = ft_split(data->envp[i], ':');
			i = 0;
			while (data->paths[i])
			{
				data->paths[i] = ft_strjoin(data->paths[i], "/");
                i++;
			}
			data->paths[0] = ft_strtrim(data->paths[0], "PATH=");
			return ;
		}
		i++;
	}
    i = 0;
	write(2, "Environment variables not found\n", 32);
	exit(0);
}

char    *find_cmd(t_data *data)
{
    int     i;
    char    *tmp;

    i = 0;
    while (data->paths[i])
    {
        tmp = ft_strjoin(data->paths[i], data->av[2]);
        if (access(tmp, F_OK | X_OK) == 0)
        {
            printf("%s\n", tmp);
            return (tmp);
        }
        i++;
    }
    return (NULL);
}

void    check_files(t_data *data)
{
    if (access(data->av[1], F_OK) == 0)
    {
        printf("%s\n", data->av[1]);
        return ;
    }
}
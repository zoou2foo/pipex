/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 08:05:05 by valeriejean       #+#    #+#             */
/*   Updated: 2022/11/05 11:37:22 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	find_cmds(t_data *data)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 2;
	printf("%d\n", data->ac);
	while (data->av[j] && j < data->ac - 2)
	{
		while (data->paths[i])
		{
			tmp = ft_strjoin(data->paths[i], data->av[j]);
			if (access(tmp, F_OK | X_OK) == 0)
			{
				printf("Trouvé: %s\n", tmp);
			}
			i++;
		}
		j++;
	}
}

// ! Check_files to adapt to look at the file in av[1] and the file at av[ac -1]
void	check_files(t_data *data)
{
	printf("what the fuck am I doing???\n");
	while (data->av[1] && data->av[data->ac - 1])
	{
		if (access(data->av[1], F_OK) == 0 && access(data->av[data->ac - 1], F_OK) == 0)
		{
			printf("went through access\n");
			return ;
		}
	}
}

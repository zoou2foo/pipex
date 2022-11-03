/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 08:05:05 by valeriejean       #+#    #+#             */
/*   Updated: 2022/11/03 17:50:29 by vjean            ###   ########.fr       */
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
	while (data->paths[i])
	{
		while (data->av[j] && data->av[data->ac - 2])
		{
			tmp = ft_strjoin(data->paths[i], data->av[j]);
			if (access(tmp, F_OK | X_OK) == 0)
			{
				printf("%s\n", tmp);
				return ;
			}
			i++;
		}
		j++;
	}
}

void	check_files(t_data *data)
{
	printf("what the fuck am I doing???");
	while (data->av[1] && data->av[data->ac - 1])
	{
		if (access(data->av[1], F_OK) == 0 && access(data->av[data->ac - 1], F_OK) == 0)
		{
			printf("went through access");
			return ;
		}
	}
}

// char	*find_cmd(t_data *data)
// {
// 	int		i;
// 	char	*tmp;

// 	i = 0;
// 	while (data->paths[i])
// 	{
// 		tmp = ft_strjoin(data->paths[i], data->av[2]);
// 		if (access(tmp, F_OK | X_OK) == 0)
// 		{
// 			printf("%s\n", tmp);
// 			return (tmp);
// 		}
// 		i++;
// 	}
// 	return (NULL);
// } 

// void	check_files(t_data *data)
// {
// 	if (access(data->av[1], F_OK) == 0)
// 	{
// 		printf("%s\n", data->av[1]);
// 		return ;
// 	}
// }
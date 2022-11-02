/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getting_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 09:07:11 by vjean             #+#    #+#             */
/*   Updated: 2022/11/02 19:30:57 by vjean            ###   ########.fr       */
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
	write(2, "Environment variables not found\n", 32);
	exit(0);
}

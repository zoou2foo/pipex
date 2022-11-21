/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 08:35:30 by vjean             #+#    #+#             */
/*   Updated: 2022/11/17 16:06:27 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_struct(int ac, char **av, char **envp, t_data *data)
{
	data->ac = ac;
	data->av = av;
	data->envp = envp;
}

void	fill_tab_env(t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], "PATH=", 5) == 0)
		{
			data->paths = ft_split(data->envp[i], ':');
			i = 0;
			while (data->paths[i])
			{
				tmp = ft_strjoin(data->paths[i], "/");
				free(data->paths[i]);
				data->paths[i] = tmp;
				i++;
			}
			*data->paths[0] += 5;
			return ;
		}
		i++;
	}
	i = 0;
	write(2, "Environment variables not found\n", 32);
	exit(0);
}

char	*find_cmd(t_data *data)
{
	int		i;
	char	*cmd;

	i = 0;
	if (ft_strncmp(data->cmd[0], "/", 1) == 0)
	{
		if (access(*data->cmd, X_OK) == 0)
			return (*data->cmd);
	}
	while (data->paths[i])
	{
		cmd = ft_strjoin(data->paths[i], *data->cmd);
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		free(cmd);
		i++;
	}
	return (NULL);
}

int	check_files(t_data *data, int index)
{
	if (index == 4)
	{
		if (access(data->av[4], F_OK | W_OK) == 0)
			return (0);
	}
	else if (index == 1)
	{
		if (access(data->av[1], F_OK | R_OK) == 0)
			return (0);
	}
	return (1);
}
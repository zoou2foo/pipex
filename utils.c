/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 08:35:30 by vjean             #+#    #+#             */
/*   Updated: 2022/11/09 14:08:37 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_struct(int ac, char **av, char **envp, t_data *data)
{
	data->ac = ac;
	data->av = av;
	data->envp = envp;
	data->path_line = -1;
}

// ! fill_tab_env need to call freetab
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

//2 child et 3 parent qui devient mon index pour find_cmd
char	*find_cmd(t_data *data, char *cmd_tab)
{
	int		i;
	char	*cmd;

	i = 0;
	while (data->paths[i++])
	{
		printf("mon data->paths: %s\n", data->paths[i]);
		cmd = ft_strjoin_free(data->paths[i], cmd_tab);
		if (access(cmd, F_OK | X_OK) == 0)
		{
			printf("Trouvé: %s\n", cmd);
			return (cmd);
		}
		free(cmd);
	}
	printf("ta yeule!\n");
	return (NULL);
}

int	check_files(t_data *data, int index)
{
	if (index == 4)
	{
		if (access(data->av[4], F_OK) == 0)
		{
			printf("found file parent\n");
			return (0);
		}
	}
	else if (index == 1)
	{
		if (access(data->av[1], F_OK) == 0)
		{
			printf("found file child\n");
			return (0);
		}
	}
	return (1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:46:07 by vjean             #+#    #+#             */
/*   Updated: 2022/12/05 12:28:47 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	data = ft_calloc(sizeof(t_data), 1);
	if (ac >= 5)
	{
		init_struct(ac, av, envp, data);
		if (ft_strncmp(data->av[1], "here_doc", ft_strlen(data->av[1])) == 0)
		{
			here_doc(data);
			data->cmds_nb -= 1;
		}
		fill_tab_env(data);
		if (data->flag_heredoc == 0)
			open_fd_in(data);
		pipex(data);
	}
	else
	{
		write(2, "Error: not enough arguments\n", 28);
		free(data);
		exit (1);
	}
	free_dbl_ptr(data->paths);
	free_dbl_ptr(data->cmd);
	free(data);
	return (0);
}

void	here_doc(t_data *data)
{
	if (data->ac >= 6)
	{
		data->flag_heredoc = 1;
		execute_hd(data);
	}
	else
	{
		write(2, ERROR_HD, ft_strlen(ERROR_HD));
		free(data);
		exit (1);
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

void	open_fd_in(t_data *data)
{
	int	fd_in;

	fd_in = open(data->av[1], O_RDONLY);
	if (fd_in < 0)
	{
		put_error_message(data, 1);
		close(fd_in);
		free_dbl_ptr(data->paths);
		free_dbl_ptr(data->cmd);
		free(data);
		exit (1);
	}
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
}

void	execute_hd(t_data *data)
{
	char	*gnl_return;
	int		pipe_hd[2];

	if (pipe(pipe_hd) == -1)
	{
		write(2, "Error: invalid pipe fd\n", 24);
		free(data);
		exit (1);
	}
	while (1)
	{
		gnl_return = gnl_pipex();
		if ((ft_strncmp(ft_strtrim(gnl_return, "\n"), data->av[2],
					ft_strlen(gnl_return))) == 0)
			break ;
		write(pipe_hd[1], gnl_return, ft_strlen(gnl_return));
		free (gnl_return);
	}
	dup2(pipe_hd[0], STDIN_FILENO);
	close(pipe_hd[0]);
	close(pipe_hd[1]);
	free (gnl_return);
}

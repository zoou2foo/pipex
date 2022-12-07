/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:45:48 by vjean             #+#    #+#             */
/*   Updated: 2022/12/07 09:25:47 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_dbl_ptr(char **ptr)
{
	int	i;

	if (ptr)
	{
		i = 0;
		while (ptr[i])
		{
			free (ptr[i]);
			i++;
		}
		free(ptr[i]);
		free (ptr);
	}
}

void	free_stuff(t_data *data)
{
	free_dbl_ptr(data->paths);
	free_dbl_ptr(data->cmd);
	free(data);
}

void	close_pipe_n_free(t_data *data, char *gnl_return)
{
	close(data->pipe_hd[0]);
	close(data->pipe_hd[1]);
	free (gnl_return);
}

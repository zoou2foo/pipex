/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:31:41 by vjean             #+#    #+#             */
/*   Updated: 2022/11/10 15:34:10 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		free (ptr);
	}
}

void	free_all_tab(t_data *data)
{
	free_dbl_ptr(data->envp);
	free_dbl_ptr(data->paths);
	free_dbl_ptr(data->av);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:45:48 by vjean             #+#    #+#             */
/*   Updated: 2022/11/15 10:46:00 by vjean            ###   ########.fr       */
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
		free(ptr[i]);
		free (ptr);
	}
}

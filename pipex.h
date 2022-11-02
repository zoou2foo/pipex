/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:44:51 by vjean             #+#    #+#             */
/*   Updated: 2022/11/02 15:54:32 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_data{
	int		ac;
	char	**av;
	char	**envp;
	int		path_line;
	char	**paths;
}	t_data;

/* functions to geth path */
void	find_path(t_data *data);
void	find_path_line(t_data *data);
void	get_path_in_tab(t_data *data);
void	fill_tab_env(t_data *data);

/* functions to fork and pipe */

/* functions to help me see what the fork I'm doing! HA HA HA */
void	print_tab(t_data *data);

#endif
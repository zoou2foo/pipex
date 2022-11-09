/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:44:51 by vjean             #+#    #+#             */
/*   Updated: 2022/11/09 13:12:22 by vjean            ###   ########.fr       */
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
	int		pipe_fd[2];
}	t_data;

/* function to organize my struct */
void	init_struct(int ac, char **av, char **envp, t_data *data);

/* functions to check arguments received */
void	fill_tab_env(t_data *data);
char	*find_cmd(t_data *data, char *cmd_tab);
int		check_files(t_data *data, int index);

/* functions all about processes */
void	pipex(t_data *data);
void	child_process(t_data *data);
void	execute_child(t_data *data, char *cmd_path, char **cmd);
void	execute_parent(t_data *data, char *cmd_path, char **cmd);
void	parent_process(t_data *data);



#endif
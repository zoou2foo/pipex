/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 08:37:33 by vjean             #+#    #+#             */
/*   Updated: 2022/11/16 15:08:25 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_data{
	int		ac;
	char	**av;
	char	**envp;
	char	**paths;
	char	**paths_slash;
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
void	execute_child2(t_data *data, char *cmd_path, char **cmd);
void	child2_process(t_data *data);

/* functions to free struff */
void	free_dbl_ptr(char **ptr);

/* helpful functions to support other functions */
int		size_of_tab(char **tab);
int		check_fds(t_data *data);

/* deal with here_doc */
void	here_doc(t_data *data);
char	*gnl_pipex(void);

#endif
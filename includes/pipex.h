/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:44:51 by vjean             #+#    #+#             */
/*   Updated: 2022/12/05 12:16:27 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_data{
	int		ac;
	int		fd_in;
	int		fd_out;
	char	**av;
	char	**envp;
	char	**paths;
	char	*cmd_path;
	char	**cmd;
	int		pipe_fd[2];
	int		pid1;
	int		pid2;
}	t_data;

/* Error message */
# define ERROR_CMD "Error: command does not exist\n"
# define ERROR_PIPE "Error: invalid pipe fd\n"
# define NO_CMD "Error: no command\n"

/* function to organize my struct */
void	init_struct(int ac, char **av, char **envp, t_data *data);

/* functions to check arguments received */
void	fill_tab_env(t_data *data);
char	*find_cmd(t_data *data);
void	check_args(t_data *data);

/* functions all about processes */
void	pipex(t_data *data);
void	child_process(t_data *data);
void	execute_child(t_data *datad);
void	execute_child2(t_data *data);
void	child2_process(t_data *data);

/* functions to free stuff */
void	free_dbl_ptr(char **ptr);
void	free_stuff(t_data *data);

/* helpful functions to support other functions */
void	close_n_wait(t_data *data);
void	put_error_message(t_data *data);
void	open_n_check(t_data *data);

#endif
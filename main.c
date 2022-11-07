/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 11:33:23 by vjean             #+#    #+#             */
/*   Updated: 2022/11/07 08:15:00 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	data = ft_calloc(sizeof(t_data), 1);
	if (ac == 5) // à mettre == 5
	{
		data->ac = ac;
		data->av = av;
		data->envp = envp;
		data->path_line = -1;
		fill_tab_env(data);
		//find_cmd(data);
		check_files(data);
		find_cmds(data);
	}
}

void	find_path(t_data *data)
{
	fill_tab_env(data);
}
// split des commandes. Exemple "grep a". Un devra être fait dans le parent et
// autre dans child. 
// & NEXT: pipe et fork()
// ! Ajouter les protections à ce que j'ai fait so far. Free des trucs
// TODO 3. Vérifier que les fichiers passés en args existent. 4.
// TODO comprendre pipe. 5. Faire pipe et redirection. 6. Comprendre fork.
// TODO 7. Faire fork() 8. Comprendre et comment il fonctionne execve 9. execve
// TODO 10. gérer les erreurs si execve fail.  
// ~ Basically, il faut que je me balade dans mon tab 2d (paths) et que je
// ~ strjoin la cmd reçu dans av[1] et av[2]. Même si la commande n'existe pas,
// ~ envoyer le résultat à execve(), la fonction va se charger d'un message
// ~ d'erreur

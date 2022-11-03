/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valeriejean <valeriejean@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:45:02 by vjean             #+#    #+#             */
/*   Updated: 2022/11/03 09:29:43 by valeriejean      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	data = ft_calloc(sizeof(t_data), 1);
	if (ac == 3) // à mettre == 5
	{
		data->ac = ac;
		data->av = av;
		data->envp = envp;
		data->path_line = -1;
		fill_tab_env(data);
		find_cmd(data);
		check_files(data);
	}
}

// & Now, besoin de mettre le tout ensemble. Avec les 5 arguments...
// ! Ajouter les protections à ce que j'ai fait so far. Free des trucs
// TODO 1. regarder si les commandes existent; 2. gérer les erreurs si la commande
// TODO n'existe pas. 3. Vérifier que les fichiers passés en args existent. 4.
// TODO comprendre pipe. 5. Faire pipe et redirection. 6. Comprendre fork.
// TODO 7. Faire fork() 8. Comprendre et comment il fonctionne execve 9. execve
// TODO 10. gérer les erreurs si execve fail.  
// ~ Basically, il faut que je me balade dans mon tab 2d (paths) et que je
// ~ strjoin la cmd reçu dans av[1] et av[2]. Même si la commande n'existe pas,
// ~ envoyer le résultat à execve(), la fonction va se charger d'un message d'erreur
// vérifier où se trouve la commande dans les paths. Si pas là, retourne le nom
// de la commande non trouvé. Même s'il n'existe pas, on l'envoie
// a execv pis il s'occupe de renvoyer erreur. But: feed les bons arguments
// à execv.
// fonctions pour trouver les paths
// fonction pour ramasser le retour lorsque la commande est trouvé => split pour
// qu'execv regarde l'option. Ex: "ls -l", qu'il prenne -l
// execve(char *cmd_path, char **args)
// grep t a  path = /bin/grep args = {grep, t, a, 0}
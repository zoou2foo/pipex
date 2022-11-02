/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:45:02 by vjean             #+#    #+#             */
/*   Updated: 2022/11/02 16:19:04 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	data = ft_calloc(sizeof(t_data), 1);
	if (ac == 2) // à mettre == 5
	{
		data->ac = ac;
		data->av = av;
		data->envp = envp;
		data->path_line = -1;
		find_path(data);
	}
}

// vérifier où se trouve la commande dans les paths. Si pas là, retourne le nom
// de la commande non trouvé. Même s'il n'existe pas, on l'envoie
// a execv pis il s'occupe de renvoyer erreur. But: feed les bons arguments
// à execv.
// fonctions pour trouver les paths
// fonction pour ramasser le retour lorsque la commande est trouvé => split pour
// qu'execv regarde l'option. Ex: "ls -l", qu'il prenne -l
// execve(char *cmd_path, char **args)
// grep t a  path = /bin/grep args = {grep, t, a, 0}
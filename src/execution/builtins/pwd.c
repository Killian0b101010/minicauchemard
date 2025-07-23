/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:26:17 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/23 18:53:36 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * Implémente la commande built-in pwd (print working directory).
 *
 * Cette fonction affiche le répertoire de travail courant, reproduisant
 * le comportement standard de la commande pwd:
 * - Utilise getcwd() pour obtenir le chemin absolu courant
 * - Affiche le chemin complet suivi d'un retour à la ligne
 * - Gère les erreurs avec perror() si getcwd() échoue
 * - Ne prend aucun argument (t2 est ignoré)
 *
 * Parameters :
 * - t2 - Structure de données (non utilisée)
 *
 * Return : 0 en cas de succès
 */
int	pwd(t_t2 *t2)
{
	char	cwd[10000];

	(void)t2;
	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_printf("%s\n", cwd);
	}
	else
		perror("getcwd");
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:32:04 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/01 05:19:36 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * Implémente la commande built-in exit pour quitter le shell.
 *
 * Cette fonction termine l'exécution du shell de manière propre
 * en appelant exit() avec un code de retour de 0:
 * - Termine immédiatement le processus du shell
 * - Retourne un code de sortie de 0 (succès)
 * - Libère automatiquement toutes les ressources
 * - Reproduit le comportement standard de la commande exit
 *
 * Parameters :
 * - Aucun
 *
 * Return : N/A (la fonction ne retourne jamais)
 */

void	exit2(t_env *env)
{
	int	i;

	i = 0;
	while (i < 1024)
		close2(i++);
	rl_clear_history();
	free_arena(env->arena);
	exit(g_exit_status);
}

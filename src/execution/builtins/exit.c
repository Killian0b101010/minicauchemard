/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:32:04 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/03 19:02:25 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	close_all_fds2(void)
{
	int	i;

	i = 0;
	while (i < 1024)
	{
		close2(i);
		i++;
	}
}

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
	close_all_fds2();
	rl_clear_history();
	free_arena(env->arena);
	exit(g_exit_status);
}

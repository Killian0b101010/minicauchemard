/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:32:04 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/28 21:09:43 by dnahon           ###   ########.fr       */
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
void	exit2(void)
{
	int	i;

	i = 0;
	while (i < 1024)
		close2(i++);
	rl_clear_history();
	exit(g_exit_status);
}

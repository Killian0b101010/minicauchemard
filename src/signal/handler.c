/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:40:24 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/26 22:46:00 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_handler(int sig)
{
	(void)sig;
	g_exit_status = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/**
 * Configure les gestionnaires de signaux pour le mode interactif du shell.
 *
 * Cette fonction initialise la gestion des signaux lors que le shell
 * est en mode interactif (en attente d'entrée utilisateur):
 * - SIGINT (Ctrl+C) : Utilise ft_handler pour une gestion propre
 * - SIGQUIT (Ctrl+\) : Ignoré pour éviter la terminaison
 * - Maintient l'interface utilisateur responsive
 * - Assure un comportement cohérent avec les shells standards
 *
 * Parameters :
 * - Aucun
 *
 * Return : Aucun (void)
 */
void	setup_interactive_signals(void)
{
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * Configure les gestionnaires de signaux pour les processus enfants.
 *
 * Cette fonction restaure le comportement par défaut des signaux
 * pour les processus enfants exécutant des commandes:
 * - SIGINT (Ctrl+C) : Comportement par défaut (terminaison)
 * - SIGQUIT (Ctrl+\) : Comportement par défaut (core dump)
 * - Permet aux commandes d'être interrompues normalement
 * - Respecte les attentes des programmes externes
 *
 * Parameters :
 * - Aucun
 *
 * Return : Aucun (void)
 */
void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

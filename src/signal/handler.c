/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:40:24 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/05 18:17:34 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_handler(int sig)
{
	int	*active_shell;

	(void)sig;
	g_exit_status = 130;
	active_shell = is_active_shell(NULL);
	if (*active_shell == 2)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_handler_sigquit(int sig)
{
	int	*active_shell;

	(void)sig;
	g_exit_status = 131;
	active_shell = is_active_shell(NULL);
	if (*active_shell == 2)
	{
		write(1, "Quit (core dumped)\n", 19);
		exit(g_exit_status);
	}
}

void	process_commands_signal(t_cmd_block *blocks, int i)
{
	int	status;

	if (blocks->fd->pid[i] != -1)
	{
		waitpid(blocks->fd->pid[i], &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			g_exit_status = 128 + WTERMSIG(status);
			if (WTERMSIG(status) == SIGQUIT)
				write(2, "Quit (core dumped)\n", 19);
			else if (WTERMSIG(status) == SIGINT)
				write(2, "\n", 1);
		}
	}
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
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, ft_handler_sigquit);
}

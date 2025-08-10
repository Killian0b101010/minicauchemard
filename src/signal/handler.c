/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:40:24 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/10 19:08:31 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_handler(int sig)
{
	int	*active_shell;
	int	signal_received;

	(void)sig;
	g_exit_status = 130;
	signal_received = 1;
	get_signal_received(&signal_received);
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
	int	signal_received;

	(void)sig;
	g_exit_status = 131;
	signal_received = 2;
	get_signal_received(&signal_received);
	active_shell = is_active_shell(NULL);
	if (*active_shell == 2)
		exit(g_exit_status);
}

void	ft_handler_heredoc(int sig)
{
	(void)sig;
	g_exit_status = 130;
	write(STDOUT_FILENO, "\n", 1);
	close(STDIN_FILENO);
}

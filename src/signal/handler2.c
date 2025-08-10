/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 19:08:35 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/10 19:08:35 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_commands_signal(t_cmd_block *blocks, int i)
{
	int	status;

	status = 0;
	if (blocks->fd->pid[i] != -1)
	{
		if (waitpid(blocks->fd->pid[i], &status, 0) > 0)
		{
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				g_exit_status = 128 + WTERMSIG(status);
			}
		}
	}
}

void	setup_interactive_signals(void)
{
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_heredoc_signals(void)
{
	signal(SIGINT, ft_handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_child_signals(void)
{
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, ft_handler_sigquit);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:29:37 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/03 20:29:37 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_pipes2(int i, t_fd *fd, t_arena *arena)
{
	fd->pipefd = arena_alloc(arena, sizeof(int *) * (fd->cmd_count - 1));
	while (i < fd->cmd_count - 1)
	{
		fd->pipefd[i] = arena_alloc(arena, sizeof(int) * 2);
		pipe(fd->pipefd[i++]);
	}
}

void	init_pipex(t_arena *arena, t_cmd_block *blocks, t_t2 t2, t_fd *fd)
{
	blocks->fd->pid = arena_alloc(arena, sizeof(pid_t) * t2.block_count);
	if (!blocks->fd->pid)
		exit(EXIT_FAILURE);
	init_pipes2(0, fd, arena);
}

void	close_unused_pipes(t_fd *fd, int i)
{
	if (i > 0)
	{
		close2(fd->pipefd[i - 1][0]);
		close2(fd->pipefd[i - 1][1]);
	}
}

void	close_all_fds(t_fd *fd)
{
	int	j;

	j = 0;
	while (j < fd->cmd_count - 1)
	{
		close2(fd->pipefd[j][0]);
		close2(fd->pipefd[j++][1]);
	}
}

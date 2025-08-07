/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:29:37 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/05 21:03:33 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	setup_child_pipes(int i, t_cmd_block *blocks)
{
	int	j;
	int	has_heredoc;

	t((j = 0, has_heredoc = has_heredoc_in_block(blocks[i].tokens,
				blocks[i].t2.token_count), 0));
	if (i == 0)
	{
		if (blocks->fd->cmd_count > 1)
			dup2(blocks->fd->pipefd[0][1], 1);
	}
	else if (i == blocks->fd->cmd_count - 1)
	{
		if (!has_heredoc)
			dup2(blocks->fd->pipefd[i - 1][0], 0);
	}
	else
	{
		if (!has_heredoc)
			dup2(blocks->fd->pipefd[i - 1][0], 0);
		dup2(blocks->fd->pipefd[i][1], 1);
	}
	while (j < blocks->fd->cmd_count - 1)
		t((close2(blocks->fd->pipefd[j][0]), close2(blocks->fd->pipefd[j++][1]),
				0));
	close_inherited_fds();
}

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

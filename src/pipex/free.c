/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:54:24 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/29 18:17:04 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	ft_error(char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 21);
	exit(127);
}

void	close_unused_pipes(t_fd *fd, int i)
{
	if (i > 0)
	{
		close2(fd->pipefd[i - 1][0]);
		close2(fd->pipefd[i - 1][1]);
	}
}

void	cleanup_and_exit(t_fd *fd, int code)
{
	close_all_fds(fd);
	free_all(fd);
	exit(code);
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
	if (fd->fd_in > 0)
		close2(fd->fd_in);
	if (fd->fd_out > 0)
		close2(fd->fd_out);
}

void	free_all(t_fd *fd)
{
	int	i;

	i = 0;
	while (i < fd->cmd_count - 1)
		free(fd->pipefd[i++]);
	free(fd->pipefd);
	free(fd->pid);
}

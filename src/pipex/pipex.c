/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:37:50 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/10 17:43:13 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	open_files(char *infile, char *outfile, t_fd *fd)
{
	fd->fd_in = open(infile, O_RDONLY);
	if (fd->fd_in == -1)
		perror(infile);
	fd->fd_out = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd->fd_out == -1)
		perror(outfile);
}

void	init_pipes(int i, t_fd *fd)
{
	fd->pipefd = ft_malloc(sizeof(int *) * (fd->cmd_count - 1));
	while (i < fd->cmd_count - 1)
	{
		fd->pipefd[i] = ft_malloc(sizeof(int) * 2);
		pipe(fd->pipefd[i++]);
	}
}

void	if_negative_fd(int i, t_fd *fd)
{
	if (i == 0 && fd->fd_in == -1)
		cleanup_and_exit(fd, 1);
	if (i == fd->cmd_count - 1 && fd->fd_out == -1)
		cleanup_and_exit(fd, 1);
}

void	close_files(t_fd *fd)
{
	if (fd->fd_in > 0)
		close2(fd->fd_in);
	if (fd->fd_out > 0)
		close2(fd->fd_out);
}

pid_t	child_process(int i, char **av, char **envp, t_fd *fd)
{
	pid_t	pid;
	int		j;

	t((j = 0, pid = fork(), 0));
	if (pid == 0)
	{
		if_negative_fd(i, fd);
		if (i == 0)
			t((dup2(fd->fd_in, 0), dup2(fd->pipefd[0][1], 1), 0));
		else if (i == fd->cmd_count - 1)
			t((dup2(fd->pipefd[i - 1][0], 0), dup2(fd->fd_out, 1), 0));
		else
			t((dup2(fd->pipefd[i - 1][0], 0), dup2(fd->pipefd[i][1], 1), 0));
		while (j < fd->cmd_count - 1)
			t((close2(fd->pipefd[j][0]), close2(fd->pipefd[j++][1]), 0));
		close_files(fd);
		if (av[i + fd->cmd_start] && av[i + fd->cmd_start][0])
			t((execute_cmd(av[i + fd->cmd_start], envp), free_all(fd),
					ft_error(av[i + fd->cmd_start]), 0));
		else
			t((close_all_fds(fd), free_all(fd), ft_error(av[i + 2]), 0));
	}
	return (pid);
}

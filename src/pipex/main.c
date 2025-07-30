/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:53:10 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/29 17:58:06 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	t(int a)
{
	(void)a;
}

void	init_here_doc(int ac, char **av, t_fd *fd)
{
	if (ac < 6)
		exit((write(2,
					"Usage: ./pipex here_doc \"limiter\" \"cmd1\" \"cmd2\" outfile\n",
					57), 1));
	fd->cmd_count = ac - 4;
	fd->pid = ft_malloc(sizeof(pid_t) * fd->cmd_count);
	if (!fd->pid)
		exit(EXIT_FAILURE);
	init_pipes(0, fd);
	open_files_heredoc(av, av[ac - 1], fd);
	unlink(".heredoc_tmp");
	fd->cmd_start = 3;
}

void	init_pipex(int ac, char **av, t_fd *fd)
{
	fd->cmd_count = ac - 3;
	fd->pid = ft_malloc(sizeof(pid_t) * fd->cmd_count);
	if (!fd->pid)
		exit(EXIT_FAILURE);
	init_pipes(0, fd);
	open_files(av[1], av[ac - 1], fd);
	fd->cmd_start = 2;
}

int	main(int ac, char **av, char **envp)
{
	t_fd	fd;
	int		status;
	int		i;

	if (ac < 5)
		exit((write(2, "Usage: ./pipex infile \"cmd1\" \"cmd2\" outfile\n", 44),
				1));
	i = -1;
	status = 0;
	if (!ft_strncmp(av[1], "here_doc", 8))
		init_here_doc(ac, av, &fd);
	else
		init_pipex(ac, av, &fd);
	while (++i < fd.cmd_count)
		t((fd.pid[i] = child_process(i, av, envp, &fd), close_unused_pipes(&fd,
					i), 0));
	t((close2(fd.fd_in), close2(fd.fd_out), i = 0, 0));
	while (i < fd.cmd_count)
		if (fd.pid[i] > 0)
			waitpid(fd.pid[i++], &status, 0);
	free_all(&fd);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

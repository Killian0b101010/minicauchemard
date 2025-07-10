/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:08:54 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/08 19:59:22 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	open_files_heredoc(char **av, char *outfile, t_fd *fd)
{
	char	*infile;

	infile = ".heredoc_tmp";
	fd->fd_in = open(infile, O_CREAT | O_WRONLY, 0644);
	if (fd->fd_in == -1)
		perror(infile);
	read_heredoc_input(av[2], fd->fd_in);
	close(fd->fd_in);
	fd->fd_in = open(infile, O_RDONLY);
	if (fd->fd_in == -1)
		perror(infile);
	fd->fd_out = open(outfile, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (fd->fd_out == -1)
		perror(outfile);
}

void	read_heredoc_input(char *limiter, int fd_tmp)
{
	char	*line;
	size_t	limiter_len;

	limiter_len = ft_strlen(limiter);
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, limiter_len) == 0
			&& line[limiter_len] == '\n')
		{
			free(line);
			break ;
		}
		write(fd_tmp, line, ft_strlen(line));
		free(line);
	}
	get_next_line(-1);
}

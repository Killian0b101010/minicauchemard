/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:10:17 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/02 17:27:32 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../libft/includes/libft.h"
# include <errno.h>
# include <sys/wait.h>

typedef struct t_ex
{
	char	**cmdargs;
	char	**paths;
	char	*cmd_path;
	ssize_t	i;
	char	*full_cmd;
	int		errcode;

}			t_data;

// void		t(int a);
// void		ft_error(char *cmd);
// void		cleanup_and_exit(t_fd *fd, int code);
// void		close_all_fds(t_fd *fd);
// void		free_all(t_fd *fd);
// void		close_unused_pipes(t_fd *fd, int i);
// void		init_pipes(int i, t_fd *fd);
// void		open_files(char *infile, char *outfile, t_fd *fd);
// pid_t		child_process(int i, char **av, char **envp, t_fd *fd);
// void		execute_cmd(char *cmd, char **envp);
// void		exec_loop(char *cmd, char **envp, t_data *ex);
int			is_abs_path(char *cmd);
// char		**get_path(char **envp);
// char		*get_absolute_path(char *cmd, char *path);
// void		read_heredoc_input(char *limiter, int fd_tmp);
// void		open_files_heredoc(char **av, char *outfile, t_fd *fd);
void		close2(int fd);

#endif

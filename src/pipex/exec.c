/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:29:30 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/10 17:58:51 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	ft_error(char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 21);
	exit(127);
}

void	execute_cmd(char *cmd, char **envp)
{
	t_data	ex;

	ex.cmdargs = ft_split(cmd, ' ');
	if (!ex.cmdargs || !ex.cmdargs[0])
		exit((write(2, "Error\n", 6), -1));
	ex.paths = get_path(envp);
	if (!ex.paths)
		exit((write(2, "Error\n", 6), -1));
	ex.i = 0;
	while (ex.paths[ex.i])
		exec_loop(cmd, envp, &ex);
	t((ft_free_split(ex.cmdargs), ft_free_split(ex.paths), 0));
}

void	exec_loop(char *cmd, char **envp, t_data *ex)
{
	if (is_abs_path(cmd))
	{
		ex->full_cmd = get_absolute_path(ex->cmdargs[0], ex->paths[ex->i]);
		if (access(ex->full_cmd, X_OK) == 0)
			execve(ex->full_cmd, ex->cmdargs, envp);
		ft_free(ex->full_cmd);
	}
	else
	{
		ex->cmd_path = ft_strjoin(ex->paths[ex->i], "/");
		ex->full_cmd = ft_strjoin(ex->cmd_path, ex->cmdargs[0]);
		ft_free(ex->cmd_path);
		if (access(ex->full_cmd, X_OK) == 0)
			execve(ex->full_cmd, ex->cmdargs, envp);
		ft_free(ex->full_cmd);
	}
	ex->i++;
}

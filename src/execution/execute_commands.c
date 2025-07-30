/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:13:26 by kiteixei          #+#    #+#             */
/*   Updated: 2025/07/30 05:26:16 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_cmd_one(t_cmd_block *block, t_env *env)
{
	if (!block->args || !block->args[0])
		return (write(2, "Error\n", 6), (void)0);
	block->path = get_path_arena(env->arena,env->envp);
	if (!block->path)
		exit((write(2, "Error\n", 6), -1));
	block->i = 0;
	block->flag_access = 0;
	if (is_builtin(block->tokens[0].value))
		return (execute_builtin_block(block, env), (void)0);
	else
	{
		while (block->path[block->i] && block->flag_access == 0)
			exec_loop_one(block, env);
	}
	if (block->flag_access == 0)
		write(2, "Command not found\n", 18);
}

void	exec_loop_one(t_cmd_block *block, t_env *env)
{
	if (is_abs_path(block->args[0]) && ft_strlen(block->args[0]) > 1)
	{
		if (access(block->args[0], X_OK) == 0)
		{
			block->full_cmd = ft_strdup_arena(env->arena, block->args[0]);
			return (block->flag_access = 1, fork_loop_one(block, env));
		}
	}
	else
	{
		block->cmd_path = ft_strjoin_arena(env->arena, block->path[block->i],
				"/");
		block->full_cmd = ft_strjoin_arena(env->arena, block->cmd_path,
				block->args[0]);
		if (access(block->full_cmd, X_OK) == 0)
			return (block->flag_access = 1, fork_loop_one(block, env));
	}
	block->i++;
}

int	is_executable_file(const char *path)
{
	struct stat	s;

	if (stat(path, &s) == 0)
	{
		if (S_ISDIR(s.st_mode))
			return (2);
		if ((s.st_mode & S_IXUSR) && !S_ISDIR(s.st_mode))
			return (1);
	}
	return (0);
}

void	fork_loop_one(t_cmd_block *block, t_env *env)
{
	pid_t	pid;
	int		stat_result;

	stat_result = is_executable_file(block->full_cmd);
	if (stat_result == 2)
	{
		write(2, "minishell: ", 11);
		write(2, block->full_cmd, ft_strlen(block->full_cmd));
		write(2, ": Is a directory\n", 17);
		return ;
	}
	if (stat_result == 1)
	{
		pid = fork();
		if (pid == 0)
		{
			execve(block->full_cmd, block->args, env->envp);
		}
		waitpid(pid, NULL, 0);
	}
}

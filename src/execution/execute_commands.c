/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:13:26 by kiteixei          #+#    #+#             */
/*   Updated: 2025/07/27 20:03:25 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	execute_piped_commands(t_cmd_block *blocks, int block_count, t_env *env)
// {
// 	int	i;

// 	i = 0;
// 	while (i < block_count)
// 	{
// 		execute_builtin_in_block(&blocks[i], env);
// 		i++;
// 	}
// }

void	execute_multiple_cmd(t_cmd_block *block, t_env *env)
{
	int	i;

	i = -1;
	while (block[++i].args[0])
	{
		if (!block[i].args || !block[i].args[0])
			return (write(2, "Error\n", 6), (void)0);
		block[i].path = get_path(env->envp);
		if (!block[i].path)
			exit((write(2, "Error\n", 6), -1));
		block[i].i = 0;
		block[i].flag_access = 0;
		if (is_builtin(block[i].tokens[0].value))
			return (execute_builtin_block(block, env),
				ft_free_split(block[i].path), (void)0);
		else
		{
			while (block[i].path[block[i].i] && block[i].flag_access == 0)
				exec_loop_one(block, env, i);
		}
		if (block[i].flag_access == 0)
		{
			write(2, block[i].args[0], ft_strlen(block[i].args[0]));
			write(2, ": Command not found\n", 21);
			g_exit_status = 127;
		}
		t((ft_free_split(block[i].args), ft_free_split(block[i].path), 0));
	}
}

void	execute_cmd_one(t_cmd_block *block, t_env *env)
{
	int	i;

	i = 0;
	if (!block[0].args || !block[0].args[0])
		return (write(2, "Error\n", 6), (void)0);
	block[0].path = get_path(env->envp);
	if (!block[0].path)
		exit((write(2, "Error\n", 6), -1));
	block[0].i = 0;
	block[0].flag_access = 0;
	if (is_builtin(block[0].tokens[0].value))
		return (execute_builtin_block(block, env), ft_free_split(block[0].path),
			(void)0);
	else
	{
		while (block[0].path[block[0].i] && block[0].flag_access == 0)
			exec_loop_one(block, env, i);
	}
	if (block[0].flag_access == 0)
	{
		write(2, block[0].args[0], ft_strlen(block[0].args[0]));
		write(2, ": Command not found\n", 21);
		g_exit_status = 127;
	}
	t((ft_free_split(block[0].args), ft_free_split(block[0].path), 0));
}

void	exec_loop_one(t_cmd_block *block, t_env *env, int i)
{
	if (is_abs_path(block[i].args[0]))
	{
		if (access(block[i].args[0], X_OK) == 0)
		{
			block[i].full_cmd = ft_strdup(block[i].args[0]);
			return (block[i].flag_access = 1, fork_loop_one(block, env, i));
		}
	}
	else
	{
		block[i].cmd_path = ft_strjoin(block[i].path[block[i].i], "/");
		block[i].full_cmd = ft_strjoin(block[i].cmd_path, block[i].args[0]);
		ft_free(block[i].cmd_path);
		if (access(block[i].full_cmd, X_OK) == 0)
			return (block[i].flag_access = 1, fork_loop_one(block, env, i));
	}
	block[i].i++;
}

int	is_executable_file(const char *path)
{
	struct stat	s;

	if (stat(path, &s) == 0)
	{
		// C'est un dossier ? => interdit !
		if (S_ISDIR(s.st_mode))
			return (2); // Is a directory
		// C'est un exécutable ?
		if ((s.st_mode & S_IXUSR) && !S_ISDIR(s.st_mode))
			return (1); // C'est exécutable
	}
	return (0); // Pas trouvé ou pas exécutable
}

void	fork_loop_one(t_cmd_block *block, t_env *env, int i)
{
	pid_t	pid;
	int		stat_result;

	stat_result = is_executable_file(block[i].full_cmd);
	if (stat_result == 2)
	{
		write(2, "minicauchemar: ", 16);
		write(2, block[i].args[0], ft_strlen(block[i].args[0]));
		write(2, ": Is a directory\n", 17);
		return ;
	}
	if (stat_result == 1)
	{
		pid = fork();
		if (pid == 0)
		{
			execve(block[i].full_cmd, block[i].args, env->envp);
		}
		waitpid(pid, NULL, 0);
		ft_free(block[i].full_cmd);
	}
}

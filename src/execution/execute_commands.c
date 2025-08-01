/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:13:26 by kiteixei          #+#    #+#             */
/*   Updated: 2025/08/01 21:09:05 by dnahon           ###   ########.fr       */
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

// void	ft_error(char *cmd)
// {
// 	write(2, cmd, ft_strlen(cmd));
// 	write(2, ": command not found\n", 21);
// 	exit(127);
// }

// void	close_unused_pipes(t_fd *fd, int i)
// {
// 	if (i > 0)
// 	{
// 		close2(fd->pipefd[i - 1][0]);
// 		close2(fd->pipefd[i - 1][1]);
// 	}
// }

// void	cleanup_and_exit(t_fd *fd, int code)
// {
// 	close_all_fds(fd);
// 	free_all(fd);
// 	exit(code);
// }

// void	if_negative_fd(int i, t_fd *fd)
// {
// 	if (i == 0 && fd->fd_in == -1)
// 		cleanup_and_exit(fd, 1);
// 	if (i == fd->cmd_count - 1 && fd->fd_out == -1)
// 		cleanup_and_exit(fd, 1);
// }

// pid_t	child_process(int i, char **av, char **envp, t_fd *fd)
// {
// 	pid_t	pid;
// 	int		j;

// 	t((j = 0, pid = fork(), 0));
// 	if (pid == 0)
// 	{
// 		if_negative_fd(i, fd);
// 		t((dup2(fd->pipefd[i - 1][0], 0), dup2(fd->pipefd[i][1], 1), 0));
// 		while (j < fd->cmd_count - 1)
// 			t((close2(fd->pipefd[j][0]), close2(fd->pipefd[j++][1]), 0));
// 		close_files(fd);
// 		if (av[i + fd->cmd_start] && av[i + fd->cmd_start][0])
// 			t((execute_cmd(av[i + fd->cmd_start], envp), free_all(fd),
// 					ft_error(av[i + fd->cmd_start]), 0));
// 		else
// 			t((close_all_fds(fd), free_all(fd), ft_error(av[i + 2]), 0));
// 	}
// 	return (pid);
// }

// void	execute_multiple_cmd(t_cmd_block *block, t_env *env)
// {
// 	if (!block->args || !block->args[0])
// 		return (write(2, "Error\n", 6), (void)0);
// 	block->path = get_path(env->envp);
// 	if (!block->path)
// 		exit((write(2, "Error\n", 6), -1));
// 	block->i = 0;
// 	block->flag_access = 0;
// 	if (is_builtin(block->tokens[0].value))
// 		return (execute_builtin_block(block, env), ft_free_split(block->path),
// 			(void)0);
// 	else
// 	{
// 		while (block->path[block->i] && block->flag_access == 0)
// 			exec_loop_one(block, env);
// 	}
// 	if (block->flag_access == 0)
// 		write(2, "Command not found\n", 18);
// 	t((ft_free_split(block->args), ft_free_split(block->path), 0));
// }

void	if_nopath(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, ": No such file or directory\n", 29);
	g_exit_status = 127;
}

void	execute_cmd_one(t_cmd_block *block, t_env *env)
{
	if (!block->args[0] && block->is_here_doc == 0)
		return ;
	if ((!block->args || !block->args[0]))
		return (write(2, "Error\n", 7), (void)0);
	if (!block->args || !block->args[0])
		return (write(2, "Error\n", 7), (void)0);
	block->path = get_path_arena(env->arena, env->envp);
	if (!block->path)
		return (if_nopath(block->args[0]), (void)0);
	block->i = 0;
	block->flag_access = 0;
	block->is_here_doc = 0;
	if (is_builtin(block->tokens[0].value))
		return (execute_builtin_block(block, env), (void)0);
	else
	{
		while (block->path[block->i] && block->flag_access == 0)
			exec_loop_one(block, env);
	}
	if (block->flag_access == 0)
	{
		write(2, block->args[0], ft_strlen(block->args[0]));
		write(2, ": command not found\n", 21);
		g_exit_status = 127;
	}
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
		if (block->args[0][0] == '\0')
			return (write(2, "minicauchemar: Command '' not found\n", 37),
				(void)0);
		write(2, "minicauchemar: ", 16);
		write(2, block->args[0], ft_strlen(block->args[0]));
		write(2, ": Is a directory\n", 17);
		return ;
	}
	if (stat_result == 1)
	{
		g_exit_status = 0;
		pid = fork();
		if (pid == 0)
		{
			execve(block->full_cmd, block->args, env->envp);
		}
		waitpid(pid, NULL, 0);
	}
}

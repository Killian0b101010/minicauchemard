/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:13:26 by kiteixei          #+#    #+#             */
/*   Updated: 2025/08/05 18:19:25 by kiteixei         ###   ########.fr       */
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

void	execute_child_command(int i, t_cmd_block *blocks, t_env *env)
{
	int	cmd_valid;

	blocks[i].is_here_doc = 0;
	if (handle_redirections(blocks[i].tokens, blocks[i].t2.token_count) == -1)
		t((blocks[i].is_here_doc = 1, free_arena(env->arena), exit(1), 0));
	setup_child_pipes(i, blocks);
	if (blocks[i].args[0] && blocks[i].args[0][0])
	{
		cmd_valid = is_command_valid_for_exec(&blocks[i], env);
		if (cmd_valid > 0)
			execute_cmd2(&blocks[i], env);
		else
			t((write(2, blocks[i].args[0], ft_strlen(blocks[i].args[0])),
					write(2, ": command not found\n", 21),
					free_arena(env->arena), exit(127), 0));
	}
	else
		t((free_arena(env->arena), exit(0), 0));
}

pid_t	child_process2(int i, t_cmd_block *blocks, t_env *env)
{
	pid_t	pid;

	setup_child_signals();
	if (blocks[i].args[0] && is_builtin(blocks[i].tokens[0].value)
		&& blocks->fd->cmd_count >= 1)
	{
		if (ft_strcmp(blocks[i].tokens[0].value, "export") == 0
			|| ft_strcmp(blocks[i].tokens[0].value, "unset") == 0
			|| ft_strcmp(blocks[i].tokens[0].value, "cd") == 0
			|| ft_strcmp(blocks[i].tokens[0].value, "exit") == 0)
			return (execute_builtin_block(&blocks[i], env), -1);
	}
	pid = fork();
	if (pid == 0)
	{
		execute_child_command(i, blocks, env);
	}
	return (pid);
}

void	exec_loop_one(t_cmd_block *block, t_env *env)
{
	if (is_abs_path(block->args[0]) && ft_strlen(block->args[0]) > 1)
	{
		if (access(block->args[0], X_OK) == 0)
		{
			block->full_cmd = ft_strdup_arena(env->arena, block->args[0]);
			return (block->flag_access = 1, exec_if_executable(block, env));
		}
	}
	else
	{
		block->cmd_path = ft_strjoin_arena(env->arena, block->path[block->i],
				"/");
		block->full_cmd = ft_strjoin_arena(env->arena, block->cmd_path,
				block->args[0]);
		if (access(block->full_cmd, X_OK) == 0)
			return (block->flag_access = 1, exec_if_executable(block, env));
	}
	block->i++;
}

void	exec_if_executable(t_cmd_block *block, t_env *env)
{
	int	stat_result;

	stat_result = is_executable_file(block->full_cmd);
	if (stat_result == 2)
	{
		if (block->args[0][0] == '\0')
			return (write(2, "minicauchemar: Command '' not found\n", 37),
				(void)0);
		write(2, "minicauchemar: ", 16);
		write(2, block->args[0], ft_strlen(block->args[0]));
		write(2, ": Is a directory\n", 17);
		exit(g_exit_status);
	}
	if (stat_result == 1)
	{
		g_exit_status = 0;
		if (execve(block->full_cmd, block->args, env->envp) == -1)
		{
			free_arena(env->arena);
			exit(127);
		}
	}
}

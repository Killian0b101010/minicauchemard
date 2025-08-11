/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_processing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:00:00 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/11 15:39:49 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_cmd2(t_cmd_block *blocks, t_env *env)
{
	if (!blocks->args[0] && blocks->is_here_doc == 0)
		exit(0);
	if ((!blocks->args || !blocks->args[0]))
		exit((write(2, "Error\n", 7), 1));
	if (!blocks->args || !blocks->args[0])
		exit((write(2, "Error\n", 7), 1));
	blocks->path = get_path_arena(env->arena, env->envp);
	if (!blocks->path)
	{
		if (ft_strchr(blocks->args[0], '/'))
			exec_loop_one(blocks, env);
		else
			exit((if_nopath(blocks->args[0]), free_arena(env->arena), 127));
	}
	t((blocks->i = 0, blocks->flag_access = 0, blocks->is_here_doc = 0, 0));
	while (blocks->path[blocks->i])
		exec_loop_one(blocks, env);
	flagaccesscheck(blocks, env);
	exit(0);
}

void	process_commands(t_cmd_block *blocks, t_env *env, int block_count,
		int i)
{
	int	*signal_received;

	blocks->fd = arena_alloc(env->arena, sizeof(t_fd));
	if (!blocks->fd)
		return ;
	blocks->fd->cmd_count = block_count;
	blocks->t2.block_count = block_count;
	init_pipex(env->arena, blocks, blocks->t2, blocks->fd);
	while (++i < block_count)
	{
		blocks->fd->pid[i] = child_process2(i, blocks, env);
		close_unused_pipes(blocks->fd, i);
	}
	close_all_fds(blocks->fd);
	i = -1;
	while (++i < block_count)
		process_commands_signal(blocks, i);
	signal_received = get_signal_received(NULL);
	if (signal_received && *signal_received == 1)
		write(1, "\n", 1);
	else if (signal_received && *signal_received == 2)
		write(1, "Quit (core dumped)\n", 19);
}

int	process_input_line(char *input, t_env *env)
{
	t_token		*tokens;
	t_cmd_block	*blocks;
	t_t2		t2;
	int			i;
	int			block_count;

	i = -1;
	if (!verify_input(input, &t2.single_quotes, &t2.double_quotes))
		return (0);
	input = expand_exit_status_in_string(env->arena, input);
	tokens = tokenizer(env->arena, input, &t2.token_count);
	if (!tokens || t2.token_count == 0)
		if (tokens)
			return (1);
	process_token_expansion(tokens, t2.token_count, env);
	if (verify_token_syntax(tokens, &t2) == 1)
		return (g_exit_status = 2, 1);
	if (parse_syntax(tokens, t2.token_count) == 1)
		return (g_exit_status = 2, 1);
	if (pipe_syntax(tokens, t2) == 1)
		return (g_exit_status = 2, 1);
	if (preprocess_heredocs(env, tokens, t2.token_count) == -1)
		return (0);
	blocks = split_into_blocks(env->arena, tokens, t2, &block_count);
	return (process_commands(blocks, env, block_count, i), 1);
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

void	if_nopath(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, ": No such file or directory\n", 29);
	g_exit_status = 127;
}

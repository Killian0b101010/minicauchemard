/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_processing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:00:00 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/04 21:48:28 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

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
		exit((if_nopath(blocks->args[0]), 127));
	t((blocks->i = 0, blocks->flag_access = 0, blocks->is_here_doc = 0, 0));
	while (blocks->path[blocks->i])
		exec_loop_one(blocks, env);
	flagaccesscheck(blocks);
	exit(0);
}

void	process_commands(t_cmd_block *blocks, t_env *env, int block_count,
		int i)
{
	int	status;

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
	i = 0;
	while (i < block_count)
	{
		if (blocks->fd->pid[i] != -1)
		{
			waitpid(blocks->fd->pid[i], &status, 0);
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
		}
		i++;
	}
}

int	parse_syntax(t_cmd_block *blocks, int token_count)
{
	int				i;
	t_token_type	type;

	i = -1;
	if (token_count >= 1)
	{
		while (++i < token_count)
		{
			type = blocks->tokens[i].type;
			if (type == REDIRECT_IN)
			{
				if (i + 1 >= token_count || blocks->tokens[i + 1].type != WORD)
					return (write(2, NEWLINE_SYNTAX, ft_strlen(NEWLINE_SYNTAX)),
						1);
			}
			else if (type == REDIRECT_OUT || type == HEREDOC || type == APPEND)
			{
				if (i + 1 >= token_count || blocks->tokens[i + 1].type != WORD)
					return (write(2, NEWLINE_SYNTAX, ft_strlen(NEWLINE_SYNTAX)),
						1);
			}
		}
	}
	return (0);
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
	if (preprocess_heredocs(env, tokens, t2.token_count) == -1)
		return (0);
	blocks = split_into_blocks(env->arena, tokens, t2, &block_count);
	while (++i < block_count)
	{
		if (!blocks[i].args[0])
			return (write(2, PIPE_SYNTAX, ft_strlen(PIPE_SYNTAX)), 1);
	}
	i = -1;
	if (parse_syntax(blocks, t2.token_count) == 1)
		return (1);
	process_commands(blocks, env, block_count, i);
	return (1);
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

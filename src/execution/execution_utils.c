/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:00:00 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/15 17:22:45 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_builtin_block(t_cmd_block *block, t_env *env)
{
	if (!block->tokens || block->t2.token_count == 0)
		return (1);
	if (ft_strcmp(block->tokens[0].value, "pwd") == 0)
		return (pwd(&block->t2));
	if (ft_strcmp(block->tokens[0].value, "echo") == 0)
		return (echo(block->tokens, block->t2.token_count));
	if (ft_strcmp(block->tokens[0].value, "env") == 0)
		return (env_cmd(0, env, block->tokens, &block->t2));
	if (ft_strcmp(block->tokens[0].value, "cd") == 0)
		return (cd_builtin(block->tokens, block->t2.token_count, env));
	if (ft_strcmp(block->tokens[0].value, "export") == 0)
		return (export(env, block->tokens, block->t2.token_count));
	if (ft_strcmp(block->tokens[0].value, "unset") == 0)
		return (unset(env, block->tokens, block->t2.token_count));
	if (ft_strcmp(block->tokens[0].value, "exit") == 0)
	{
		exit2();
		return (0);
	}
	return (127);
}

static int	execute_single_block(t_cmd_block *blocks, t_env *env)
{
	execute_with_redirections(&blocks[0], env);
	return (1);
}

static int	execute_multiple_blocks(t_cmd_block *blocks, int block_count,
		t_env *env)
{
	execute_piped_commands(blocks, block_count, env);
	return (1);
}

int	process_input_line(char *input, t_env *env)
{
	t_token		*tokens;
	t_cmd_block	*blocks;
	t_t2		t2;
	int			block_count;

	t2.env_count = 0;
	t2.pwd_count = 0;
	tokens = tokenizer(input, &t2.token_count);
	if (!tokens)
		return (0);
	process_token_expansion(tokens, t2.token_count, env);
	blocks = split_into_blocks(tokens, t2, &block_count);
	if (!blocks)
	{
		free_tokens(tokens, t2.token_count);
		return (0);
	}
	if (block_count == 1)
		execute_single_block(blocks, env);
	else
		execute_multiple_blocks(blocks, block_count, env);
	free_cmd_blocks(blocks, block_count);
	free_tokens(tokens, t2.token_count);
	return (1);
}

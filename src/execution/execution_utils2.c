/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:46:10 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/31 04:38:23 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	verify_input(char *input, t_t2 t2)
{
	if (is_empty_input(input))
		return (0);
	if (!count_quotes(input, &t2.single_quotes, &t2.double_quotes))
		return (0);
	return (1);
}

void	execute_piped_commands(t_cmd_block *blocks, int block_count, t_env *env)
{
	int	i;

	i = 0;
	while (i < block_count)
	{
		execute_builtin_in_block(&blocks[i], env);
		i++;
	}
}

void	execute_builtin_in_block(t_cmd_block *block, t_env *env)
{
	char	*cmd;

	if (!block->tokens || block->t2.token_count == 0)
		return ;
	cmd = block->tokens[0].value;
	if (ft_strcmp(cmd, "pwd") == 0)
		pwd(&block->t2);
	else if (ft_strcmp(cmd, "echo") == 0)
		echo(block->tokens, block->t2.token_count);
	else if (ft_strcmp(cmd, "env") == 0)
		env_cmd(0, env, block->tokens, &block->t2);
	else if (ft_strcmp(cmd, "cd") == 0)
		cd_builtin(block->tokens, block->t2.token_count, env);
	else if (ft_strcmp(cmd, "export") == 0)
		export_builtin(env, block->tokens, block->t2.token_count);
	else if (ft_strcmp(cmd, "unset") == 0)
		unset(env, block->tokens, block->t2.token_count);
	else if (ft_strcmp(cmd, "exit") == 0)
		exit2(env);
	else
		return ;
}

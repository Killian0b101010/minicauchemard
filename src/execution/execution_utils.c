/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:46:10 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/08 14:41:33 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	verify_input(char *input, int *single_quotes, int *double_quotes)
{
	if (is_empty_input(input))
		return (0);
	if (!count_quotes(input, single_quotes, double_quotes))
		return (0);
	return (1);
}

void	flagaccesscheck(t_cmd_block *blocks, t_env *env)
{
	if (blocks->flag_access == 0)
	{
		if_nopath(blocks->args[0]);
		free_arena(env->arena);
		exit(127);
	}
}

static int	check_command_in_path(char **path, t_cmd_block *block, t_env *env)
{
	char	*cmd_path;
	char	*full_cmd;
	int		i;
	int		result;

	i = -1;
	while (path[++i])
	{
		cmd_path = ft_strjoin_arena(env->arena, path[i], "/");
		full_cmd = ft_strjoin_arena(env->arena, cmd_path, block->args[0]);
		result = is_executable_file(full_cmd);
		if (result == 1)
			return (1);
		else if (result == 2)
			return (directory_error(block->args[0]), -1);
	}
	return (0);
}

int	is_command_valid_for_exec(t_cmd_block *block, t_env *env)
{
	char	**path;
	int		result;

	if (!block->args[0])
		return (0);
	if (is_builtin(block->args[0]))
		return (1);
	if (is_abs_path(block->args[0]) && ft_strlen(block->args[0]) > 1)
	{
		result = is_executable_file(block->args[0]);
		if (result == 2)
			return (directory_error(block->args[0]), -1);
		return (result == 1);
	}
	path = get_path_arena(env->arena, env->envp);
	if (!path)
		return (0);
	return (check_command_in_path(path, block, env));
}

int	has_heredoc_in_block(t_token *tokens, int token_count)
{
	int	i;

	i = 0;
	while (i < token_count)
	{
		if (tokens[i].type == HEREDOC)
			return (1);
		i++;
	}
	return (0);
}

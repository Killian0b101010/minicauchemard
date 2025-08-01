/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:45:09 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/01 05:09:11 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	exec_builtins(t_token *tokens, int token_count, t_env *env, t_t2 *t2)
{
	char	*cmd;

	if (!tokens || token_count == 0)
		return (1);
	cmd = tokens[0].value;
	if (ft_strcmp(cmd, "echo") == 0)
		return (echo(tokens, token_count));
	if (ft_strcmp(cmd, "cd") == 0)
		return (cd_builtin(tokens, token_count, env));
	if (ft_strcmp(cmd, "pwd") == 0)
		return (pwd(t2));
	if (ft_strcmp(cmd, "export") == 0)
		return (export_builtin(env, tokens, token_count));
	if (ft_strcmp(cmd, "unset") == 0)
		return (unset(env, tokens, token_count));
	if (ft_strcmp(cmd, "env") == 0)
		return (env_cmd(0, env, tokens, t2));
	if (ft_strcmp(cmd, "exit") == 0)
	{
		exit2(env);
		return (0);
	}
	return (1);
}

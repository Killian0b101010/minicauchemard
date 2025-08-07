/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:45:09 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/06 02:48:22 by dnahon           ###   ########.fr       */
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

/**

 * Exécute une commande built-in en identifiant
 * et appelant la fonction appropriée.
 *
 * Cette fonction gère l'exécution des commandes intégrées du shell:
 * - Expanse d'abord les variables $? dans les arguments
 * - Identifie la commande built-in à exécuter
 * - Appelle la fonction correspondante avec les bons paramètres
 * - Met à jour g_exit_status avec le code de retour
 * - Gère le cas spécial de la commande exit
 *
 * Parameters :
 * - block - Bloc de commande contenant la built-in à exécuter
 * - env - Structure d'environnement du shell
 *
 * Return : Code de retour de la commande exécutée
 */
int	execute_builtin_block(t_cmd_block *block, t_env *env)
{
	int	result;

	if (!block->tokens || block->t2.token_count == 0)
		return (1);
	if (ft_strcmp(block->tokens[0].value, "pwd") == 0)
		result = pwd(&block->t2);
	else if (ft_strcmp(block->tokens[0].value, "echo") == 0)
		result = echo(block->tokens, block->t2.token_count);
	else if (ft_strcmp(block->tokens[0].value, "env") == 0)
		result = env_cmd(0, env, block->tokens, &block->t2);
	else if (ft_strcmp(block->tokens[0].value, "cd") == 0)
		result = cd_builtin(block->tokens, block->t2.token_count, env);
	else if (ft_strcmp(block->tokens[0].value, "export") == 0)
		result = export_builtin(env, block->tokens, block->t2.token_count);
	else if (ft_strcmp(block->tokens[0].value, "unset") == 0)
		result = unset(env, block->tokens, block->t2.token_count);
	else if (ft_strcmp(block->tokens[0].value, "exit") == 0
		&& block->t2.block_count == 1)
		return (exit_builtin(block, env), 0);
	else
		result = 127;
	return (g_exit_status = result, result);
}

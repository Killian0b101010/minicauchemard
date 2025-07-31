/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:00:00 by dnahon            #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

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
	else if (ft_strcmp(block->tokens[0].value, "exit") == 0)
		return (exit2(env), 0);
	else
		result = 127;
	return (g_exit_status = result, result);
}

// static int	execute_single_block(t_cmd_block *blocks, t_env *env)
// {
// 	int	result;

// 	result = execute_with_redirections(&blocks[0], env);
// 	return (result);
// }

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

	t((t2.env_count = 0, t2.pwd_count = 0, 0));
	if (!verify_input(input, t2))
		return (0);
	input = expand_exit_status_in_string(env->arena, input);
	tokens = tokenizer(env->arena, input, &t2.token_count);
	if (!tokens || t2.token_count == 0)
	{
		if (tokens)
			return (1);
	}
	process_token_expansion(tokens, t2.token_count, env);
	blocks = split_into_blocks(env->arena, tokens, t2, &block_count);
	if (!blocks)
		return (0);
	if (block_count == 1)
		execute_with_redirections(blocks, env);
	else
	{
		// execute_multiple_cmd(blocks, env);
		execute_multiple_blocks(blocks, block_count, env);
		return (1);
	}
	return (1);
}

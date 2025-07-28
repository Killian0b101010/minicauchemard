/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:00:00 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/28 20:42:35 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

/**
 * Expanse les variables $? dans tous les tokens WORD du bloc de commande.
 *
 * Cette fonction parcourt tous les tokens du bloc et remplace les occurrences
 * de $? par la valeur actuelle de g_exit_status:
 * - Parcourt tous les tokens du bloc
 * - Traite uniquement les tokens de type WORD
 * - Utilise expand_exit_status_in_string() pour l'expansion
 * - Libère l'ancienne valeur et assigne la nouvelle
 *
 * Parameters :
 * - block - Bloc de commande contenant les tokens à traiter
 *
 * Return : Aucun (void)
 */
static void	expand_exit_status_in_block(t_cmd_block *block)
{
	int		i;
	char	*expanded;

	i = 0;
	while (i < block->t2.token_count)
	{
		if (block->tokens[i].type == WORD)
		{
			expanded = expand_exit_status_in_string(block->tokens[i].value);
			if (expanded)
			{
				ft_free(block->tokens[i].value);
				block->tokens[i].value = expanded;
			}
		}
		i++;
	}
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
	expand_exit_status_in_block(block);
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
		return (exit2(), 0);
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
	tokens = tokenizer(input, &t2.token_count);
	if (!tokens || t2.token_count == 0)
	{
		if (tokens)
			free_tokens(tokens, t2.token_count);
		return (1);
	}
	process_token_expansion(tokens, t2.token_count, env);
	blocks = split_into_blocks(tokens, t2, &block_count);
	if (!blocks)
		return (free_tokens(tokens, t2.token_count), 0);
	if (block_count == 1)
		execute_with_redirections(blocks, env);
	else
	{
		// execute_multiple_cmd(blocks, env);
		execute_multiple_blocks(blocks, block_count, env);
		free_cmd_blocks(blocks, block_count);
	}
	return (free_tokens(tokens, t2.token_count), 1);
}

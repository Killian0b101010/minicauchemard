/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:09:52 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/26 20:47:46 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Remplit un bloc de commande avec les tokens et arguments correspondants.
 *
 * Cette fonction initialise un bloc de commande en copiant les tokens
 * et en construisant le tableau d'arguments:
 * - Construit les arguments avec build_cmd_args()
 * - Alloue la mémoire pour les tokens du bloc
 * - Copie chaque token (valeur, type, quoted) dans le bloc
 * - Met à jour le compteur de tokens du bloc
 *
 * Parameters :
 * - block - Bloc de commande à remplir
 * - tokens - Tableau source des tokens
 * - start - Index de début dans le tableau de tokens
 * - end - Index de fin dans le tableau de tokens
 *
 * Return : 1 en cas de succès, 0 si échec d'allocation
 */
int	fill_block(t_cmd_block *block, t_token *tokens, int start, int end)
{
	int	k;
	int	count;

	count = end - start;
	block->args = build_cmd_args(&tokens[start], count);
	block->tokens = ft_malloc(sizeof(t_token) * count);
	if (!block->args || !block->tokens)
		return (0);
	k = -1;
	while (++k < count)
	{
		block->tokens[k].value = ft_strdup(tokens[start + k].value);
		block->tokens[k].type = tokens[start + k].type;
		block->tokens[k].quoted = tokens[start + k].quoted;
	}
	block->t2.token_count = count;
	return (1);
}

/**
 * Divise un tableau de tokens en blocs de commandes séparés par des pipes.
 *
 * Cette fonction analyse les tokens pour créer des blocs de commandes
 * indépendants, chacun correspondant à une commande dans un pipeline:
 * - Compte les pipes pour déterminer le nombre de blocs
 * - Alloue la mémoire pour tous les blocs
 * - Remplit chaque bloc avec ses tokens correspondants
 * - Gère les erreurs d'allocation avec nettoyage automatique
 *
 * Parameters :
 * - tokens - Tableau des tokens à diviser
 * - t2 - Structure contenant le nombre de tokens
 * - block_count - Pointeur vers le nombre de blocs créés
 *
 * Return : Tableau de blocs de commandes ou NULL si échec
 */
t_cmd_block	*split_into_blocks(t_token *tokens, t_t2 t2, int *block_count)
{
	t_cmd_block	*blocks;
	int			i;
	int			j;
	int			start;

	*block_count = count_pipes(tokens, t2.token_count) + 1;
	blocks = ft_malloc(sizeof(t_cmd_block) * (*block_count));
	if (!blocks)
		return (NULL);
	t((i = 0, j = 0, start = 0, 0));
	while (i <= t2.token_count)
	{
		if (i == t2.token_count || tokens[i].type == PIPE)
		{
			if (!fill_block(&blocks[j], tokens, start, i))
				return (free_cmd_blocks(blocks, j), NULL);
			if (i < t2.token_count)
				tokens[i].value = NULL;
			start = i + 1;
			j++;
		}
		i++;
	}
	return (blocks);
}

void	print_cmd_blocks(t_cmd_block *blocks, int block_count)
{
	int	i;
	int	j;

	i = -1;
	while (++i < block_count)
	{
		printf("📦 Bloc %d:\n", i);
		printf("  Args: ");
		if (!blocks[i].args)
			printf("(none)\n");
		else
		{
			j = -1;
			while (blocks[i].args[++j])
				printf("\"%s\" ", blocks[i].args[j]);
			printf("\n");
		}
		printf("  Tokens: ");
		j = -1;
		while (++j < blocks[i].t2.token_count)
			printf("[%s] ", blocks[i].tokens[j].value);
		printf("\n\n");
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
		exit2();
	else
		return ;
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

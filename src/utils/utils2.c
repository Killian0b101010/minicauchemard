/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:09:52 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/31 16:14:36 by dnahon           ###   ########.fr       */
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
int	fill_block(t_arena *arena, t_cmd_block *block, t_token *tokens, int start,
		int end)
{
	int	k;
	int	count;

	count = end - start;
	block->args = build_cmd_args(arena, &tokens[start], count);
	block->tokens = arena_alloc(arena, (count) * sizeof(t_token));
	if (!block->args || !block->tokens)
		return (0);
	k = -1;
	while (++k < count)
	{
		block->tokens[k].value = ft_strdup_arena(arena, tokens[start
				+ k].value);
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
t_cmd_block	*split_into_blocks(t_arena *arena, t_token *tokens, t_t2 t2,
		int *block_count)
{
	t_cmd_block	*blocks;
	int			i;
	int			j;
	int			start;

	*block_count = count_pipes(tokens, t2.token_count) + 1;
	blocks = arena_alloc(arena, *block_count * sizeof(t_cmd_block));
	t2.block_count = *block_count;
	if (!blocks)
		return (NULL);
	t((i = 0, j = 0, start = 0, 0));
	while (i <= t2.token_count)
	{
		if (i == t2.token_count || tokens[i].type == PIPE)
		{
			if (!fill_block(arena, &blocks[j], tokens, start, i))
				return (NULL);
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

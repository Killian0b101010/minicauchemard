/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:09:52 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/08 18:35:27 by kiteixei         ###   ########.fr       */
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
int	fill_block(t_arena *arena, t_cmd_block *block, t_token *tokens)
{
	int	k;
	int	count;

	count = block->split_blocks_i - block->split_start;
	block->args = build_cmd_args(arena, &tokens[block->split_start], count);
	block->tokens = arena_alloc(arena, (count) * sizeof(t_token));
	if (!block->args || !block->tokens)
		return (0);
	k = -1;
	while (++k < count)
	{
		block->tokens[k].value = ft_strdup_arena(arena,
				tokens[block->split_start + k].value);
		block->tokens[k].type = tokens[block->split_start + k].type;
		block->tokens[k].quoted = tokens[block->split_start + k].quoted;
		block->tokens[k].heredoc_fd = tokens[block->split_start + k].heredoc_fd;
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

	*block_count = count_pipes(tokens, t2.token_count) + 1;
	blocks = arena_alloc(arena, *block_count * sizeof(t_cmd_block));
	t2.block_count = *block_count;
	ft_bzero(blocks, *block_count * sizeof(t_cmd_block));
	if (!blocks)
		return (NULL);
	t((i = 0, j = 0, 0));
	blocks[j].split_start = 0;
	while (i <= t2.token_count)
	{
		if (i == t2.token_count || tokens[i].type == PIPE)
		{
			blocks[j].split_blocks_i = i;
			if (!fill_block(arena, &blocks[j], tokens))
				return (NULL);
			if (i < t2.token_count)
				t((j++, blocks[j].split_start = i + 1, 0));
		}
		i++;
	}
	return (blocks);
}

void	close_inherited_fds(void)
{
	int	i;

	i = 3;
	while (i < 1024)
	{
		close(i);
		i++;
	}
}

void	print_cmd_blocks(t_cmd_block *blocks, int block_count)
{
	int	i;
	int	j;

	i = -1;
	while (++i < block_count)
	{
		ft_printf("📦 Bloc %d:\n", i);
		ft_printf("  Args: ");
		if (!blocks[i].args)
			ft_printf("(none)\n");
		else
		{
			j = -1;
			while (blocks[i].args[++j])
				ft_printf("\"%s\" ", blocks[i].args[j]);
			ft_printf("\n");
		}
		ft_printf("  Tokens: ");
		j = -1;
		while (++j < blocks[i].t2.token_count)
			ft_printf("[%s] ", blocks[i].tokens[j].value);
		ft_printf("\n\n");
	}
}

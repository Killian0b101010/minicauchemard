/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_collector.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 04:38:22 by kiteixei          #+#    #+#             */
/*   Updated: 2025/07/30 04:04:21 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*safe_malloc(void **ptr, size_t size)
{
	if (*ptr != NULL)
	{
		ft_putstr_fd("Error,double malloc\n", 2);
		return (NULL);
	}
	if (*ptr == NULL)
	{
		*ptr = malloc(size);
		if (!*ptr)
			return (NULL);
	}
	return (*ptr);
}
t_arena	*arena_init(size_t initial_capacity)
{
	t_arena	*arena;

	arena = NULL;
	// Initialise l'arene
	if (!safe_malloc((void **)&arena, sizeof(t_arena)))
	{
		ft_putstr_fd("Failed to allocate arena \n", 2);
		exit(1);
	}
	// On creer un espace initial pour les block de memoire
	arena->arena_memory = malloc(initial_capacity * sizeof(void *));
	if (!arena->arena_memory)
	{
		ft_putstr_fd("Failed to allocate arena storage \n", 2);
		free(arena);
		return (NULL);
	}
	// Initialisation des variable pour la gestion de la memoire
	arena->capacity = initial_capacity;
	arena->actual_size = 0;
	arena->size = 0;
	return (arena);
}

void	*arena_alloc(t_arena *arena, size_t size_block)
{
	void	*block;

	// Allocation du block memoire pour stocker mon malloc en fonction de size_block
	block = malloc(size_block);
	if (!block)
		return (NULL);
	// J'incremente mon actual_size pour check si ja
	if (arena->actual_size == arena->capacity)
	{
		arena->capacity *= 2;
		arena->arena_memory = realloc(arena->arena_memory, arena->capacity
				* sizeof(void *));
		if (!arena->arena_memory)
			return (NULL);
	}
	arena->arena_memory[arena->actual_size] = block;
	arena->actual_size++;
	return (block);
}

void	free_arena(t_arena *arena)
{
	size_t	i;

	i = 0;
	if (!arena)
		return ;
	if (arena->arena_memory)
	{
		while (i < arena->actual_size)
			if (arena->arena_memory[i])
				free(arena->arena_memory[i++]);
		free(arena->arena_memory);
	}
	free(arena);
}

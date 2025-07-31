/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_collector.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 04:38:22 by kiteixei          #+#    #+#             */
/*   Updated: 2025/07/31 00:30:44 by kiteixei         ###   ########.fr       */
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
	if (!safe_malloc((void **)&arena, sizeof(t_arena)))
	{
		ft_putstr_fd("Failed to allocate arena \n", 2);
		exit(1);
	}
	arena->arena_memory = malloc(initial_capacity * sizeof(void *));
	if (!arena->arena_memory)
	{
		ft_putstr_fd("Failed to allocate arena storage \n", 2);
		free(arena);
		return (NULL);
	}
	arena->capacity = initial_capacity;
	arena->actual_size = 0;
	arena->size = 0;
	return (arena);
}

void	*arena_alloc(t_arena *arena, size_t size_block)
{
	void	*block;
	size_t	new_capacity;
	void	**tmp;
	size_t	old_size_bytes;
	size_t	new_size_bytes;

	block = malloc(size_block);
	if (!block)
		return (NULL);
	if (arena->actual_size == arena->capacity)
	{
		if (arena->capacity == 0)
			new_capacity = 1;
		else
			new_capacity = arena->capacity * 2;
		old_size_bytes = arena->actual_size * sizeof(void *);
		new_size_bytes = new_capacity * sizeof(void *);
		tmp = ft_realloc_arena(arena->arena_memory, old_size_bytes,
				new_size_bytes);
		if (!tmp)
			return (free(block), NULL);
		t((arena->arena_memory = tmp, arena->capacity = new_capacity, 0));
	}
	arena->arena_memory[arena->actual_size] = block;
	return (arena->actual_size++, block);
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

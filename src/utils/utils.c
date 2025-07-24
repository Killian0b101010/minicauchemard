/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:09:52 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/23 19:24:54 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	t(int a)
{
	(void)a;
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

/**
 * Réalloue un bloc mémoire avec une nouvelle taille en copiant les données.
 *
 * Cette fonction personnalisée remplace realloc() en offrant un contrôle
 * explicite sur la taille des données à copier:
 * - Gère le cas où ptr est NULL (allocation simple)
 * - Libère la mémoire si new_size est 0
 * - Copie les données existantes dans le nouveau bloc
 * - Utilise la plus petite taille entre old_size et new_size
 *
 * Parameters :
 * - ptr - Pointeur vers le bloc mémoire à réallouer
 * - old_size - Taille actuelle du bloc mémoire
 * - new_size - Nouvelle taille désirée
 *
 * Return : Pointeur vers le nouveau bloc mémoire ou NULL si échec
 */
void	*realloc2(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (!ptr)
		return (ft_malloc(new_size));
	if (new_size == 0)
	{
		ft_free(ptr);
		return (NULL);
	}
	new_ptr = ft_malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (old_size < new_size)
		ft_memcpy(new_ptr, ptr, old_size);
	else
		ft_memcpy(new_ptr, ptr, new_size);
	ft_free(ptr);
	return (new_ptr);
}

void	print_syntax_error(char *value)
{
	write(2, "minishell: syntax error near unexpected token '", 48);
	write(2, value, ft_strlen(value));
	write(2, "'\n", 2);
}

int	count_pipes(t_token *tokens, int token_count)
{
	int	i;
	int	pipes;

	i = 0;
	pipes = 0;
	while (i < token_count)
	{
		if (tokens[i].type == PIPE)
			pipes++;
		i++;
	}
	return (pipes);
}

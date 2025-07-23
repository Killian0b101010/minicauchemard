/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:09:52 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/23 18:53:36 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Fonction utilitaire pour ignorer une variable (évite les warnings).
 *
 * Cette fonction sert uniquement à supprimer les avertissements du compilateur
 * pour les variables non utilisées:
 * - Marque explicitement une variable comme inutilisée
 * - Évite les warnings "unused variable"
 * - Utilisée dans les macros et fonctions de debug
 * - Aucun effet sur l'exécution du programme
 *
 * Parameters :
 * - a - Variable entière à ignorer
 *
 * Return : Aucun (void)
 */
void	t(int a)
{
	(void)a;
}

/**
 * Vérifie si un caractère est un espace blanc.
 *
 * Cette fonction détermine si un caractère fait partie des espaces blancs
 * reconnus par le shell:
 * - Espace (0x20)
 * - Tabulation (0x09)
 * - Retour à la ligne (0x0A)
 * - Utilisée pour le parsing et la validation d'entrée
 *
 * Parameters :
 * - c - Caractère à tester
 *
 * Return : 1 si c'est un espace blanc, 0 sinon
 */
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

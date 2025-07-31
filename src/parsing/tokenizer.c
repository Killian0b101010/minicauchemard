/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:18:43 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/30 01:58:21 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Agrandit dynamiquement le tableau de tokens en doublant sa capacité.
 *
 * Cette fonction gère l'expansion dynamique du tableau de tokens lorsque
 * la capacité initiale est atteinte:
 * - Double la capacité du tableau
 * - Réalloue la mémoire avec realloc2()
 * - Copie les données existantes dans le nouveau tableau
 * - Met à jour le pointeur et la capacité
 *
 * Parameters :
 * - tokens - Pointeur vers le tableau de tokens à agrandir
 * - capacity - Pointeur vers la capacité actuelle (sera modifiée)
 *
 * Return : 1 en cas de succès, 0 si échec d'allocation
 */
int	expand_tokens(t_arena *arena, t_token **tokens, int *capacity)
{
	t_token	*new_tokens;
	int		old_capacity;
	int		i;

	old_capacity = *capacity;
	*capacity *= 2;
	new_tokens = arena_alloc(arena, sizeof(t_token) * (*capacity));
	if (!new_tokens)
		return (0);
	for (i = 0; i < old_capacity; i++)
		new_tokens[i] = (*tokens)[i];
	*tokens = new_tokens;
	return (1);
}

/**
 * Fonction principale de tokenisation qui analyse une ligne de commande.
 *
 * Cette fonction transforme une chaîne de caractères en tableau de tokens
 * pour le parsing du shell:
 * - Ignore les espaces blancs entre les tokens
 * - Gère les guillemets simples et doubles
 * - Identifie les opérateurs et mots
 * - Agrandit dynamiquement le tableau si nécessaire
 * - Retourne le nombre total de tokens créés
 *
 * Parameters :
 * - str - Chaîne de caractères à tokeniser
 * - token_count - Pointeur vers le compteur de tokens (sera modifié)
 *
 * Return : Tableau de tokens alloué dynamiquement ou NULL si échec
 */
t_token	*tokenizer(t_arena *arena, char *str, int *token_count)
{
	t_token	*tokens;
	t_t2	t2;
	int		capacity;

	capacity = 10;
	t((t2.index = 0, t2.i = 0, t2.j = 0, 0));
	tokens = arena_alloc(arena, (capacity) * sizeof(t_token));
	if (!tokens)
		return (NULL);
	while (str[t2.index])
	{
		while (str[t2.index] && is_space(str[t2.index]))
			t2.index++;
		if (!str[t2.index])
			break ;
		if (str[t2.index] == '"' || str[t2.index] == '\'')
			tokenize(str, &t2);
		else
			tokenize2(str, &t2);
		if (t2.j >= capacity && !expand_tokens(arena, &tokens, &capacity))
			return (NULL);
		tokenize3(arena, tokens, &t2);
	}
	*token_count = t2.j;
	return (tokens);
}

/**
 * Vérifie l'équilibrage des guillemets dans une chaîne de caractères.
 *
 * Cette fonction analyse une chaîne pour s'assurer que tous les guillemets
 * sont correctement fermés:
 * - Compte les guillemets simples et doubles séparément
 * - Vérifie que chaque type de guillemet est en nombre pair
 * - Affiche une erreur de syntaxe si des guillemets ne sont pas fermés
 * - Essentiel pour la validation de l'entrée utilisateur
 *
 * Parameters :
 * - str - Chaîne de caractères à analyser
 * - single_quotes - Pointeur vers le compteur de guillemets simples
 * - double_quotes - Pointeur vers le compteur de guillemets doubles
 *
 * Return : 1 si les guillemets sont équilibrés, 0 sinon
 */
int	count_quotes(char *str, int *single_quotes, int *double_quotes)
{
	int	i;

	i = 0;
	*single_quotes = 0;
	*double_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			(*single_quotes)++;
		else if (str[i] == '"')
			(*double_quotes)++;
		i++;
	}
	if (*single_quotes % 2 != 0 || *double_quotes % 2 != 0)
	{
		print_syntax_error("unexpected EOF");
		return (0);
	}
	return (1);
}

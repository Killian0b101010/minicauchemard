/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:18:43 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/11 15:14:03 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Agrandit dynamiquement le tableau de tokens en doublant sa capacité.
 *
 * Cette fonction gère l'expansion dynamique du tableau de tokens lorsque
 * la capacité initiale est atteinte:
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
	i = -1;
	*capacity *= 2;
	new_tokens = arena_alloc(arena, sizeof(t_token) * (*capacity));
	if (!new_tokens)
		return (0);
	while (++i < old_capacity)
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

	t((t2.index = 0, t2.i = 0, t2.j = 0, capacity = 10, 0));
	tokens = arena_alloc(arena, (capacity) * sizeof(t_token));
	if (!tokens)
		return (NULL);
	while (str[t2.index])
	{
		if (str[0] == '!' || str[0] == ':' || str[0] == '#')
			t2.index++;
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
	return (*token_count = t2.j, rm_null_tokens(tokens, token_count), tokens);
}

void	rm_null_tokens(t_token *tokens, int *token_count)
{
	int	i;
	int	shift;
	int	isnotallempty;

	t((isnotallempty = 0, shift = 0, i = 0, 0));
	while (i < *token_count && tokens[i].value)
	{
		if (tokens[i++].value[0] != '\0')
			isnotallempty = 1;
	}
	i = 0;
	if (isnotallempty == 1)
	{
		while (shift < *token_count && tokens[shift].value[0] == '\0')
			shift++;
		if (shift == 0)
			return ;
		i = 0;
		while (i < *token_count - shift)
		{
			tokens[i] = tokens[i + shift];
			i++;
		}
		*token_count -= shift;
	}
}

/**
	* Vérifie l'équilibrage des guillemets dans une chaîne de caractères.
	*
	* Cette version améliorée tient compte du contexte des guillemets:
	*
	- Un guillemet à l'intérieur d'une autre paire de guillemets n'est pas compté
	* - Utilise un état (state) pour suivre le contexte actuel
	* - STATE_NORMAL: en dehors de tout guillemet
	* - STATE_SINGLE: dans des guillemets simples
	* - STATE_DOUBLE: dans des guillemets doubles
	*
	* Parameters :
	* - str - Chaîne de caractères à analyser
	* - single_quotes - Pointeur vers le compteur de guillemets simples
	* - double_quotes - Pointeur vers le compteur de guillemets doubles
	*
	* Return : 1 si les guillemets sont équilibrés, 0 sinon
	*/

int	count_quotes(char *str, int *single_quote, int *double_quote)
{
	int	state;
	int	i;

	i = -1;
	state = STATE_NORMAL;
	*single_quote = 0;
	*double_quote = 0;
	while (str[++i])
		update_quote_state(str[i], &state, single_quote, double_quote);
	if (state != STATE_NORMAL)
	{
		print_syntax_error("unexpected EOF");
		g_exit_status = 2;
		return (0);
	}
	return (1);
}

void	update_quote_state(char c, int *state, int *single_quote,
		int *double_quote)
{
	if (*state == STATE_NORMAL)
	{
		if (c == '\'')
		{
			*state = STATE_SINGLE;
			(*single_quote)++;
		}
		else if (c == '"')
		{
			*state = STATE_DOUBLE;
			(*double_quote)++;
		}
	}
	else if (*state == STATE_SINGLE && c == '\'')
	{
		*state = STATE_NORMAL;
		(*single_quote)++;
	}
	else if (*state == STATE_DOUBLE && c == '"')
	{
		*state = STATE_NORMAL;
		(*double_quote)++;
	}
}

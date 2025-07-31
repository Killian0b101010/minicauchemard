/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:02:44 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/28 20:29:01 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * Vérifie si une chaîne représente le flag -n pour la commande echo.
 *
 * Cette fonction détermine si l'argument passé est un flag -n valide
 * qui supprime le retour à la ligne final dans echo:
 * - Vérifie que la chaîne commence par "-n"
 * - S'assure que tous les caractères suivants sont 'n'
 * - Respecte le comportement standard de echo
 * - Gère les cas comme -nnn, -nnnn, etc.
 *
 * Parameters :
 * - str - Chaîne à vérifier pour le flag -n
 *
 * Return : 1 si c'est un flag -n valide, 0 sinon
 */
static int	is_n_flag(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

/**
 * Implémente la commande built-in echo du shell.
 *
 * Cette fonction reproduit le comportement de la commande echo standard
 * en affichant les arguments passés avec support du flag -n:
 * - Détecte et traite les flags -n pour supprimer le retour à la ligne
 * - Affiche tous les arguments séparés par des espaces
 * - Ajoute un retour à la ligne final sauf si -n est présent
 * - Ignore les tokens qui ne sont pas des mots
 *
 * Parameters :
 * - tokens - Tableau des tokens de la commande
 * - token_count - Nombre total de tokens
 *
 * Return : 0 en cas de succès
 */
int	echo(t_token *tokens, int token_count)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (i < token_count && tokens[i].type == WORD
		&& is_n_flag(tokens[i].value))
	{
		n_flag = 1;
		i++;
	}
	while (i < token_count && tokens[i].type == WORD)
	{
		write(1, tokens[i].value, ft_strlen(tokens[i].value));
		if (i + 1 < token_count && tokens[i + 1].type == WORD)
			write(1, " ", 1);
		i++;
	}
	if (!n_flag)
		write(1, "\n", 1);
	return (0);
}

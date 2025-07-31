/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:08:52 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/30 03:35:24 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Joint deux chaînes et libère automatiquement la première chaîne.
 *
 * Cette fonction utilitaire combine ft_strjoin et la gestion mémoire
 * pour simplifier les opérations de concaténation répétées:
 * - Joint s1 et s2 en une nouvelle chaîne
 * - Libère automatiquement la mémoire de s1
 * - Évite les fuites mémoire dans les chaînages
 * - Optimise la gestion mémoire pour les builds graduels
 *
 * Parameters :
 * - s1 - Première chaîne (sera libérée après jointure)
 * - s2 - Deuxième chaîne (conservée)
 *
 * Return : Nouvelle chaîne résultant de la concaténation
 */
char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	ft_free(s1);
	return (joined);
}

/**
 * Convertit un entier en chaîne,
	la joint à une chaîne existante et libère la mémoire.
 *
 * Cette fonction combine la conversion d'entier et la concaténation de chaînes
 * avec une gestion automatique de la mémoire:
 * - Convertit l'entier num en chaîne de caractères
 * - Joint la chaîne résultante à str
 * - Libère toutes les variables temporaires
 * - Optimise les opérations de construction de chaînes numériques
 *
 * Parameters :
 * - str - Chaîne de base (sera libérée après jointure)
 * - num - Entier à convertir et ajouter
 *
 * Return : Nouvelle chaîne contenant str + num converti
 */
char	*join_itoa_free(char *str, int num)
{
	char	*num_str;
	char	*result;

	num_str = ft_itoa(num);
	result = ft_strjoin_free(str, num_str);
	ft_free(num_str);
	return (result);
}

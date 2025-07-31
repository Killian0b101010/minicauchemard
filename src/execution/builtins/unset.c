/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:43:47 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/29 06:24:51 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * Supprime une variable d'environnement spécifique du tableau.
 *
 * Cette fonction recherche et supprime une variable d'environnement
 * en réorganisant le tableau pour éviter les trous:
 * - Parcourt le tableau pour trouver la variable correspondante
 * - Compare le nom exactement jusqu'au '='
 * - Libère la mémoire de la variable trouvée
 * - Décale tous les éléments suivants vers la gauche
 * - Met à jour la taille du tableau
 *
 * Parameters :
 * - env - Structure d'environnement à modifier
 * - var_name - Nom de la variable à supprimer (sans '=')
 * - env_size - Pointeur vers la taille actuelle du tableau
 *
 * Return : 1 si la variable a été supprimée, 0 si non trouvée
 */
static int	remove_env_var(t_env *env, char *var_name, int *env_size)
{
	int	j;
	int	k;

	j = 0;
	while (j < *env_size && env->envp[j])
	{
		k = 0;
		while (env->envp[j][k] && env->envp[j][k] != '=' && var_name[k]
			&& env->envp[j][k] == var_name[k])
			k++;
		if (env->envp[j][k] == '=' && var_name[k] == '\0')
		{
			while (j < *env_size - 1)
			{
				env->envp[j] = env->envp[j + 1];
				j++;
			}
			env->envp[j] = NULL;
			(*env_size)--;
			return (1);
		}
		j++;
	}
	return (0);
}

/**

 * Implémente la commande built-in unset pour
 * supprimer des variables d'environnement.
 *
 * Cette fonction traite la commande unset en supprimant les variables
 * d'environnement spécifiées:
 * - Vérifie la validité des paramètres d'entrée
 * - Compte les variables d'environnement existantes
 * - Parcourt tous les arguments après "unset"
 * - Supprime chaque variable avec remove_env_var()
 *
 * Parameters :
 * - env - Structure d'environnement à modifier
 * - tokens - Tableau des tokens de la commande
 * - token_count - Nombre total de tokens
 *
 * Return : 0 en cas de succès
 */
int	unset(t_env *env, t_token *tokens, int token_count)
{
	int	i;
	int	env_size;

	if (!env || !tokens || token_count < 2)
		return (0);
	env_size = 0;
	while (env->envp[env_size])
		env_size++;
	i = 1;
	while (i < token_count)
	{
		remove_env_var(env, tokens[i].value, &env_size);
		i++;
	}
	return (0);
}

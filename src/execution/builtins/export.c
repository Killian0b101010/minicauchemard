/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:51:49 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/04 17:13:34 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * Recherche l'index d'une variable d'environnement existante.
 *
 * Cette fonction cherche si une variable d'environnement existe déjà
 * dans le tableau envp pour permettre sa mise à jour:
 * - Extrait le nom de la variable (avant le '=')
 * - Parcourt le tableau des variables d'environnement
 * - Compare les noms avec la longueur exacte
 * - Retourne l'index si trouvée, -1 sinon
 *
 * Parameters :
 * - env - Structure d'environnement à examiner
 * - var_name - Nom de la variable au format "NOM=valeur"
 *
 * Return : Index de la variable si trouvée, -1 sinon
 */
static int	find_var_index(t_env *env, char *var_name)
{
	int		i;
	int		name_len;
	char	*eq_pos;

	eq_pos = ft_strchr(var_name, '=');
	if (!eq_pos)
		return (-1);
	name_len = eq_pos - var_name;
	i = 0;
	while (env->envp[i])
	{
		if (ft_strncmp(env->envp[i], var_name, name_len) == 0
			&& env->envp[i][name_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

/**
 * Ajoute une nouvelle variable d'environnement au tableau.
 *
 * Cette fonction étend le tableau des variables d'environnement pour
 * inclure une nouvelle variable:
 * - Compte les variables existantes
 * - Alloue un nouveau tableau avec une entrée supplémentaire
 * - Copie toutes les variables existantes
 * - Ajoute la nouvelle variable à la fin
 * - Libère l'ancien tableau et met à jour le pointeur
 *
 * Parameters :
 * - env - Structure d'environnement à modifier
 * - var - Nouvelle variable au format "NOM=valeur"
 *
 * Return : 0 en cas de succès, 1 si échec d'allocation
 */
static int	add_new_var(t_env *env, char *var)
{
	int		count;
	char	**new_envp;
	int		i;

	count = 0;
	while (env->envp[count])
		count++;
	new_envp = arena_alloc(env->arena, (count + 2) * sizeof(char *));
	if (!new_envp)
		return (1);
	i = 0;
	while (i < count)
	{
		new_envp[i] = env->envp[i];
		i++;
	}
	new_envp[count] = ft_strdup_arena(env->arena, var);
	new_envp[count + 1] = NULL;
	env->envp = new_envp;
	return (0);
}

/**
 * Traite une variable d'export en la mettant à jour ou l'ajoutant.
 *
 * Cette fonction gère l'ajout ou la modification d'une variable
 * d'environnement via la commande export:
 * - Vérifie que la variable contient un '=' (format valide)
 * - Cherche si la variable existe déjà
 * - Met à jour la variable existante ou en ajoute une nouvelle
 * - Gère la mémoire en libérant l'ancienne valeur si nécessaire
 *
 * Parameters :
 * - env - Structure d'environnement à modifier
 * - var_value - Variable au format "NOM=valeur"
 *
 * Return : 0 en cas de succès, 1 si erreur
 */
static int	process_export_variable(t_env *env, char *var_value)
{
	int	var_index;

	if (var_value == NULL || ft_strchr(var_value, '=') == NULL
		|| ft_strlen(var_value) < 2)
		return (0);
	var_index = find_var_index(env, var_value);
	if (var_index >= 0)
		env->envp[var_index] = ft_strdup_arena(env->arena, var_value);
	else
	{
		if (add_new_var(env, var_value) != 0)
			return (1);
	}
	return (0);
}

/**

 * Implémente la commande built-in export pour
 * définir des variables d'environnement.
 *
 * Cette fonction traite la commande export en parcourant tous les arguments
 * et en ajoutant/modifiant les variables d'environnement:
 * - Parcourt tous les tokens après "export"
 * - Traite chaque variable avec process_export_variable()
 * - Gère les erreurs de traitement des variables
 * - Respecte le comportement standard de la commande export
 *
 * Parameters :
 * - env - Structure d'environnement à modifier
 * - tokens - Tableau des tokens de la commande
 * - token_count - Nombre total de tokens
 *
 * Return : 0 en cas de succès, 1 si erreur
 */
int	export_builtin(t_env *env, t_token *tokens, int token_count)
{
	int	i;

	i = 1;
	while (i < token_count)
	{
		if (ft_strlen(tokens[i].value) > 500)
		{
			write(2, "export: variable too long (max 500 characters)\n", 48);
			return (1);
		}
		if (process_export_variable(env, tokens[i].value) != 0)
			return (1);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:41:04 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/23 18:55:14 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * Initialise l'environnement du shell en copiant les variables système.
 *
 * Cette fonction duplique les variables d'environnement du système
 * dans la structure t_env pour usage interne du shell:
 * - Compte le nombre de variables d'environnement
 * - Alloue la mémoire nécessaire pour les stocker
 * - Duplique chaque variable d'environnement
 * - Termine le tableau par NULL
 *
 * Parameters :
 * - env - Structure d'environnement à initialiser
 * - envp - Variables d'environnement du système
 *
 * Return : Aucun (void)
 */
void	ft_set_env(t_env *env, char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (envp[i])
		i++;
	env->envp = ft_malloc(sizeof(char *) * (i + 1));
	if (!env->envp)
		return ;
	while (++j < i)
		env->envp[j] = ft_strdup(envp[j]);
	env->envp[i] = NULL;
}

/**
 * Implémente la commande built-in env pour
 * afficher les variables d'environnement.
 *
 * Cette fonction reproduit le comportement de la commande env standard
 * en affichant toutes les variables d'environnement:
 * - Vérifie qu'aucun argument supplémentaire n'est fourni
 * - Affiche un message d'erreur si un argument est donné
 * - Parcourt et affiche toutes les variables d'environnement
 * - Chaque variable est affichée au format NOM=valeur
 *
 * Parameters :
 * - index - Index de la commande dans les tokens
 * - env - Structure contenant les variables d'environnement
 * - tokens - Tableau des tokens de la commande
 * - t2 - Structure contenant le nombre de tokens
 *
 * Return : 0 en cas de succès, 1 si erreur d'argument
 */
int	env_cmd(int index, t_env *env, t_token *tokens, t_t2 *t2)
{
	int	i;

	i = 0;
	if (t2->token_count > index + 1 && tokens[index + 1].type == WORD)
	{
		write(2, "env: \'", 7);
		write(2, tokens[index + 1].value, ft_strlen(tokens[index + 1].value));
		write(2, "\': No such file or directory\n", 30);
		return (1);
	}
	else
	{
		while (env->envp[i])
		{
			ft_printf("%s\n", env->envp[i]);
			i++;
		}
	}
	return (0);
}

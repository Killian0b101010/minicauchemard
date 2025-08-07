/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:41:04 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/07 15:11:16 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	get_shlvl_index(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static char	*increment_shlvl(t_arena *arena, char *shlvl_var)
{
	int		value;
	char	*new_value_str;
	char	*new_shlvl;

	value = ft_atoi(shlvl_var + 6);
	value++;
	new_value_str = ft_itoa_arena(arena, value);
	new_shlvl = ft_strjoin_arena(arena, "SHLVL=", new_value_str);
	return (new_shlvl);
}

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
	int	shlvl_index;

	t((i = 0, j = -1, 0));
	if (!envp || !envp[0])
		return (init_bc_no_env(env), (void)0);
	while (envp[i])
		i++;
	shlvl_index = get_shlvl_index(envp);
	env->envp = arena_alloc(env->arena, (i + 2) * sizeof(char *));
	if (!env->envp)
		return ;
	while (++j < i)
	{
		if (j == shlvl_index)
			env->envp[j] = increment_shlvl(env->arena, envp[j]);
		else
			env->envp[j] = ft_strdup_arena(env->arena, envp[j]);
	}
	if (shlvl_index == -1)
		t((env->envp[i] = ft_strdup_arena(env->arena, "SHLVL=1"), env->envp[i
				+ 1] = NULL, 0));
	else
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

int	init_bc_no_env(t_env *env)
{
	char	tmp[1000];
	char	*pwd_env;

	env->envp = arena_alloc(env->arena, sizeof(char *) * 4);
	if (!env->envp)
		return (0);
	getcwd(tmp, sizeof(tmp));
	pwd_env = ft_strjoin_arena(env->arena, "PWD=", tmp);
	env->envp[0] = ft_strdup_arena(env->arena, pwd_env);
	env->envp[1] = ft_strdup_arena(env->arena, "SHLVL=1");
	env->envp[2] = ft_strdup_arena(env->arena, "_=/usr/bin/env");
	env->envp[3] = NULL;
	return (0);
}

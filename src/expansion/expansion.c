/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:50:00 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/24 18:44:14 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(char *var_name, t_env *env)
{
	int	i;
	int	len;

	if (!var_name || !env || !env->envp)
		return (NULL);
	len = ft_strlen(var_name);
	i = 0;
	while (env->envp[i])
	{
		if (ft_strncmp(env->envp[i], var_name, len) == 0
			&& env->envp[i][len] == '=')
			return (env->envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

static char	*get_variable_name(char *str, int start, int *end)
{
	int		i;
	char	*var_name;

	i = start;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	*end = i;
	if (i == start)
		return (NULL);
	var_name = ft_malloc(i - start + 1);
	if (!var_name)
		return (NULL);
	ft_strncpy(var_name, str + start, i - start);
	var_name[i - start] = '\0';
	return (var_name);
}

int	expand_variable_at_position(char *str, int i)
{
	char	*var_name;
	int		end;

	var_name = get_variable_name(str, i + 1, &end);
	if (var_name)
	{
		ft_free(var_name);
		return (end);
	}
	else
		return (i + 1);
}

char	*get_expanded_variable_value(char *str, t_env *env, int i)
{
	char	*var_name;
	char	*var_value;
	int		end;

	var_name = get_variable_name(str, i + 1, &end);
	if (var_name)
	{
		var_value = get_variable_value(var_name, env);
		ft_free(var_name);
		return (var_value);
	}
	else
		return (create_single_char_string(str, i));
}

/**

 * Expanse les occurrences de $? dans une chaîne
 * avec la valeur actuelle de g_exit_status.
 *
 * Cette fonction traite spécifiquement l'expansion de $? :
 * - Recherche toutes les occurrences de "$?"
 * - Les remplace par la valeur actuelle de g_exit_status
 * - Gère correctement l'allocation mémoire
 * - Retourne une nouvelle chaîne avec les substitutions
 *
 * Parameters :
 * - str - Chaîne d'origine pouvant contenir des "$?"
 *
 * Return : Nouvelle chaîne avec $? expansé ou NULL si erreur
 */
char	*expand_exit_status_in_string(char *str)
{
	char	*result;
	char	*temp;
	char	*exit_str;
	int		i;
	int		len;

	if (!str)
		return (NULL);
	t((result = ft_strdup(""), exit_str = ft_itoa(g_exit_status), i = 0,
			len = ft_strlen(str), 0));
	while (i < len)
	{
		if (str[i] == '$' && i + 1 < len && str[i + 1] == '?')
			t((temp = ft_strjoin(result, exit_str), ft_free(result),
					result = temp, i += 2, 0));
		else
		{
			temp = ft_malloc(ft_strlen(result) + 2);
			ft_strcpy(temp, result);
			temp[ft_strlen(result)] = str[i];
			temp[ft_strlen(result) + 1] = '\0';
			t((ft_free(result), result = temp, i++, 0));
		}
	}
	return (ft_free(exit_str), result);
}

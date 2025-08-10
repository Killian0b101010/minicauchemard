/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:50:00 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/08 17:16:50 by dnahon           ###   ########.fr       */
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

static char	*get_variable_name(t_arena *arena, char *str, int start, int *end)
{
	int		i;
	char	*var_name;

	i = start;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	*end = i;
	if (i == start)
		return (NULL);
	var_name = arena_alloc(arena, i - start + 1);
	if (!var_name)
		return (NULL);
	ft_strncpy(var_name, str + start, i - start);
	var_name[i - start] = '\0';
	return (var_name);
}

int	expand_variable_at_position(t_arena *arena, char *str, int i)
{
	char	*var_name;
	int		end;

	var_name = get_variable_name(arena, str, i + 1, &end);
	if (var_name)
	{
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

	var_name = get_variable_name(env->arena, str, i + 1, &end);
	if (var_name)
	{
		var_value = get_variable_value(var_name, env);
		return (var_value);
	}
	else
		return (create_single_char_string(env->arena, str, i));
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

char	*expand_exit_status_in_string(t_arena *arena, char *str)
{
	char	*result;
	char	*exit_str;
	int		i;
	int		len;
	char	*temp;

	if (!str)
		return (NULL);
	result = ft_strdup_arena(arena, "");
	exit_str = ft_itoa_arena(arena, g_exit_status);
	t((i = 0, len = ft_strlen(str), 0));
	while (i < len)
	{
		if (is_escaped_exit_status(str, i, len))
			i = append_escaped_exit_status(arena, &result, i);
		else if (str[i] == '$' && i + 1 < len && str[i + 1] == '?' && !(i > 0
				&& str[i - 1] == '\\'))
			i = append_expanded_exit_status(arena, &result, exit_str, i);
		else
			t((temp = arena_alloc(arena, ft_strlen(result) + 2), ft_strcpy(temp,
						result), temp[ft_strlen(result)] = str[i],
					temp[ft_strlen(result) + 1] = '\0', result = temp, i++, 0));
	}
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:30:00 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/08 17:18:28 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_var_value(char *var_name, t_env *env)
{
	char	*env_val;

	env_val = get_env_value(var_name, env);
	if (env_val)
		return (ft_strdup_arena(env->arena, env_val));
	else
		return (ft_strdup_arena(env->arena, ""));
}

char	*get_variable_name(t_arena *arena, char *str, int start, int *end)
{
	int		i;
	char	*var_name;

	i = start;
	if (str[i] == '?')
	{
		*end = i + 1;
		return (ft_strdup_arena(arena, "?"));
	}
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

char	*append_char_to_result(t_arena *arena, char *result, char c)
{
	char	*temp;

	temp = arena_alloc(arena, ft_strlen(result) + 2);
	if (temp)
	{
		ft_strcpy(temp, result);
		temp[ft_strlen(result)] = c;
		temp[ft_strlen(result) + 1] = '\0';
		return (temp);
	}
	return (result);
}

int	is_escaped_exit_status(const char *str, int i, int len)
{
	if (str[i] == '\\')
		if (i + 2 < len && str[i + 1] == '$' && str[i + 2] == '?')
			return (1);
	return (0);
}

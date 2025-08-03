/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:00:00 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/01 19:04:39 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_variable_value(char *var_name, t_env *env)
{
	char	*temp;

	temp = get_env_value(var_name, env);
	if (temp)
		return (ft_strdup_arena(env->arena, temp));
	else
		return (ft_strdup_arena(env->arena, ""));
}

char	*create_single_char_string(t_arena *arena, char *str, int i)
{
	char	*temp;

	temp = arena_alloc(arena, 2);
	if (temp)
	{
		temp[0] = str[i];
		temp[1] = '\0';
	}
	return (temp);
}

char	*expand_variables(char *str, t_env *env)
{
	if (!str)
		return (NULL);
	return (process_expansion_loop(str, env));
}

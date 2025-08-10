/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:00:00 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/08 17:12:50 by dnahon           ###   ########.fr       */
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

int	append_escaped_exit_status(t_arena *arena, char **result, int i)
{
	char	*temp;

	temp = arena_alloc(arena, ft_strlen(*result) + 3);
	ft_strcpy(temp, *result);
	temp[ft_strlen(*result)] = '$';
	temp[ft_strlen(*result) + 1] = '?';
	temp[ft_strlen(*result) + 2] = '\0';
	*result = temp;
	return (i + 3);
}

int	append_expanded_exit_status(t_arena *arena, char **result, char *exit_str,
		int i)
{
	char	*temp;

	temp = ft_strjoin_arena(arena, *result, exit_str);
	*result = temp;
	return (i + 2);
}

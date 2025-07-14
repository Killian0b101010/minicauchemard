/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:50:00 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/14 22:14:47 by dnahon           ###   ########.fr       */
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
	if (str[i] == '?')
	{
		*end = i + 1;
		return (ft_strdup("?"));
	}
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

int	expand_variable_at_position(char *str, t_env *env, int exit_status, int i)
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

char	*get_expanded_variable_value(char *str, t_env *env, int exit_status,
		int i)
{
	char	*var_name;
	char	*var_value;
	int		end;

	var_name = get_variable_name(str, i + 1, &end);
	if (var_name)
	{
		var_value = get_variable_value(var_name, env, exit_status);
		ft_free(var_name);
		return (var_value);
	}
	else
		return (create_single_char_string(str, i));
}

char	*expand_variables(char *str, t_env *env, int exit_status)
{
	if (!str)
		return (NULL);
	return (process_expansion_loop(str, env, exit_status));
}

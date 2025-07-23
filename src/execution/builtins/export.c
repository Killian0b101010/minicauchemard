/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:51:49 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/23 15:39:35 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

static int	add_new_var(t_env *env, char *var)
{
	int		count;
	char	**new_envp;
	int		i;

	count = 0;
	while (env->envp[count])
		count++;
	new_envp = ft_malloc(sizeof(char *) * (count + 2));
	if (!new_envp)
		return (1);
	i = 0;
	while (i < count)
	{
		new_envp[i] = env->envp[i];
		i++;
	}
	new_envp[count] = ft_strdup(var);
	new_envp[count + 1] = NULL;
	ft_free(env->envp);
	env->envp = new_envp;
	return (0);
}

static int	process_export_variable(t_env *env, char *var_value)
{
	int	var_index;

	if (ft_strchr(var_value, '=') == NULL)
		return (0);
	var_index = find_var_index(env, var_value);
	if (var_index >= 0)
	{
		ft_free(env->envp[var_index]);
		env->envp[var_index] = ft_strdup(var_value);
	}
	else
	{
		if (add_new_var(env, var_value) != 0)
			return (1);
	}
	return (0);
}

int	export_builtin(t_env *env, t_token *tokens, int token_count)
{
	int	i;

	i = 1;
	while (i < token_count)
	{
		if (process_export_variable(env, tokens[i].value) != 0)
			return (1);
		i++;
	}
	return (0);
}

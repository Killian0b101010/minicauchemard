/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:43:47 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/14 18:56:06 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	remove_env_var(t_env *env, char *var_name, int *env_size)
{
	int	j;
	int	k;

	j = 0;
	while (j < *env_size && env->envp[j])
	{
		k = 0;
		while (env->envp[j][k] && env->envp[j][k] != '=' && var_name[k]
			&& env->envp[j][k] == var_name[k])
			k++;
		if (env->envp[j][k] == '=' && var_name[k] == '\0')
		{
			ft_free(env->envp[j]);
			while (j < *env_size - 1)
			{
				env->envp[j] = env->envp[j + 1];
				j++;
			}
			env->envp[j] = NULL;
			(*env_size)--;
			return (1);
		}
		j++;
	}
	return (0);
}

int	unset(t_env *env, t_token *tokens, int token_count)
{
	int	i;
	int	env_size;

	if (!env || !tokens || token_count < 2)
		return (0);
	env_size = 0;
	while (env->envp[env_size])
		env_size++;
	i = 1;
	while (i < token_count)
	{
		remove_env_var(env, tokens[i].value, &env_size);
		i++;
	}
	return (0);
}

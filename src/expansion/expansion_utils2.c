/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:00:00 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/14 21:50:14 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_variable_value(char *var_name, t_env *env, int exit_status)
{
	char	*temp;

	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(exit_status));
	temp = get_env_value(var_name, env);
	if (temp)
		return (ft_strdup(temp));
	else
		return (ft_strdup(""));
}

char	*create_single_char_string(char *str, int i)
{
	char	*temp;

	temp = ft_malloc(2);
	if (temp)
	{
		temp[0] = str[i];
		temp[1] = '\0';
	}
	return (temp);
}

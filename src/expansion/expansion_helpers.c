/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:00:00 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/08 16:55:15 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_expandable_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*process_variable_expansion(char *str, t_env *env, int *i, char *result)
{
	char	*var_part;
	char	*temp;

	var_part = get_expanded_variable_value(str, env, *i);
	if (!var_part)
	{
		(*i)++;
		return (result);
	}
	if (ft_strlen(var_part) > 500)
	{
		(*i)++;
		return (result);
	}
	*i = expand_variable_at_position(env->arena, str, *i);
	temp = ft_strjoin_arena(env->arena, result, var_part);
	if (!temp)
		return (result);
	if (ft_strlen(temp) > 1000)
		return (result);
	return (temp);
}

char	*copy_escaped_variable(char *str, int *i, t_env *env, char *result)
{
	char	*temp;
	char	*variable;
	int		start;
	int		var_len;

	start = *i + 1;
	var_len = 1;
	if (str[start + var_len] == '?')
		var_len++;
	else
		while (str[start + var_len] && is_expandable_char(str[start + var_len]))
			var_len++;
	variable = arena_alloc(env->arena, var_len + 1);
	if (!variable)
		return (result);
	ft_strncpy(variable, str + start, var_len);
	variable[var_len] = '\0';
	temp = ft_strjoin_arena(env->arena, result, variable);
	*i += var_len + 1;
	if (temp)
		return (temp);
	else
		return (result);
}

char	*process_expansion_loop(char *str, t_env *env)
{
	char	*result;
	char	*temp;
	int		i;

	if (ft_strlen(str) > 1000)
		return (ft_strdup_arena(env->arena, ""));
	result = ft_strdup_arena(env->arena, "");
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] == '$')
			result = copy_escaped_variable(str, &i, env, result);
		else if (str[i] == '$' && str[i + 1] && is_expandable_char(str[i + 1]))
			result = process_variable_expansion(str, env, &i, result);
		else
		{
			temp = append_char_to_result(env->arena, result, str[i++]);
			if (!temp)
				return (result);
			result = temp;
		}
	}
	return (result);
}

void	process_token_expansion(t_token *tokens, int token_count, t_env *env)
{
	int		i;
	char	*expanded;

	i = 0;
	while (i < token_count)
	{
		if (tokens[i].type == WORD && tokens[i].quoted != 1)
		{
			expanded = expand_variables(tokens[i].value, env);
			if (expanded)
			{
				tokens[i].value = expanded;
			}
		}
		i++;
	}
}

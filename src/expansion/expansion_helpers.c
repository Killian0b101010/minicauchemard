/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:00:00 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/15 16:16:51 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_expandable_char(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '?');
}

char	*process_expansion_loop(char *str, t_env *env, int exit_status)
{
	char	*result;
	char	*temp;
	char	*var_part;
	int		i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && is_expandable_char(str[i + 1]))
		{
			var_part = get_expanded_variable_value(str, env, exit_status, i);
			i = expand_variable_at_position(str, i);
			temp = ft_strjoin(result, var_part);
			ft_free(result);
			ft_free(var_part);
			result = temp;
		}
		else
			result = append_char_to_result(result, str[i++]);
	}
	return (result);
}

void	process_token_expansion(t_token *tokens, int token_count, t_env *env,
		int exit_status)
{
	int		i;
	char	*expanded;

	i = 0;
	while (i < token_count)
	{
		if (tokens[i].type == WORD && tokens[i].quoted != 1)
		{
			expanded = expand_variables(tokens[i].value, env, exit_status);
			if (expanded)
			{
				ft_free(tokens[i].value);
				tokens[i].value = expanded;
			}
		}
		i++;
	}
}

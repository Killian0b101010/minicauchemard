/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 01:10:54 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/06 18:34:45 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_redir_type(t_token_type type)
{
	return (type == REDIRECT_IN || type == REDIRECT_OUT || type == HEREDOC
		|| type == APPEND);
}

int	parse_syntax(t_token *tokens, int token_count)
{
	int				i;
	t_token_type	type;

	i = -1;
	if (token_count >= 1)
	{
		while (++i < token_count)
		{
			type = tokens[i].type;
			if (is_redir_type(type))
			{
				if (i + 1 < token_count && is_redir_type(tokens[i + 1].type))
					return (print_syntax_error(tokens[i + 1].value), 1);
				if (i + 1 >= token_count || tokens[i + 1].type != WORD)
					return (write(2, NEWLINE_ERR_PRE NEWLINE_ERR_SUF,
							ft_strlen(NEWLINE_ERR_PRE NEWLINE_ERR_SUF)), 1);
			}
		}
	}
	return (0);
}

int	pipe_syntax(t_token *tokens, t_t2 t2)
{
	int	i;

	i = -1;
	while (++i < t2.token_count)
	{
		if (tokens[i].type == PIPE)
		{
			if (i == 0 || i == t2.token_count - 1)
				return (write(2, PIPE_SYNTAX, ft_strlen(PIPE_SYNTAX)),
					g_exit_status = 2, 1);
			if (i + 1 < t2.token_count && tokens[i + 1].type == PIPE)
				return (write(2, PIPE_SYNTAX, ft_strlen(PIPE_SYNTAX)),
					g_exit_status = 2, 1);
		}
	}
	return (0);
}

int	verify_token_syntax(t_token *tokens, t_t2 *t2)
{
	int	i;

	i = -1;
	while (++i < t2->token_count)
	{
		if (tokens[i].type == SYNTAX_ERROR)
			return (1);
	}
	return (0);
}

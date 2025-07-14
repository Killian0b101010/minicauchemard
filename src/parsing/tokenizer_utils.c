/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:07:11 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/14 18:56:04 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tokens(t_token *tokens, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		ft_free(tokens[i].value);
		i++;
	}
	ft_free(tokens);
}

t_token_type	get_token_type(char *str)
{
	if (ft_strcmp(str, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(str, "<") == 0)
		return (REDIRECT_IN);
	else if (ft_strcmp(str, ">") == 0)
		return (REDIRECT_OUT);
	else if (ft_strcmp(str, ">>") == 0)
		return (APPEND);
	else if (ft_strcmp(str, "<<") == 0)
		return (HEREDOC);
	else if (ft_strchr(str, '>') || ft_strchr(str, '<') || ft_strchr(str, '|'))
		return (SYNTAX_ERROR);
	return (WORD);
}

void	tokenize(char *str, t_t2 *t2)
{
	char	quote_char;

	quote_char = str[t2->index];
	if (quote_char == '\'')
		t2->quoted = 1;
	else
		t2->quoted = 2;
	t2->index++;
	t2->i = 0;
	while (str[t2->index] && str[t2->index] != quote_char)
		t2->buff[t2->i++] = str[t2->index++];
	t2->buff[t2->i] = '\0';
	if (str[t2->index] == quote_char)
		t2->index++;
}

void	tokenize2(char *str, t_t2 *t2)
{
	t((t2->quoted = 0, t2->i = 0, 0));
	while (str[t2->index] && !is_space(str[t2->index]) && (str[t2->index] != '"'
			&& str[t2->index] != '\''))
		t2->buff[t2->i++] = str[t2->index++];
	t2->buff[t2->i] = '\0';
}

void	tokenize3(t_token *tokens, t_t2 *t2)
{
	tokens[t2->j].value = ft_strdup(t2->buff);
	tokens[t2->j].quoted = t2->quoted;
	if (t2->quoted)
		tokens[t2->j].type = WORD;
	else
		tokens[t2->j].type = get_token_type(t2->buff);
	if (tokens[t2->j].type == SYNTAX_ERROR)
		print_syntax_error(t2->buff);
	t2->j++;
}

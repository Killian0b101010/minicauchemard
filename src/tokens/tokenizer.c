/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:18:43 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/10 22:18:07 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	expand_tokens(t_token **tokens, int *capacity)
{
	t_token	*new_tokens;
	int		old_capacity;

	old_capacity = *capacity;
	*capacity *= 2;
	new_tokens = realloc2(*tokens, sizeof(t_token) * old_capacity,
			sizeof(t_token) * (*capacity));
	if (!new_tokens)
	{
		ft_free(*tokens);
		return (0);
	}
	*tokens = new_tokens;
	return (1);
}

t_token	*tokenizer(char *str, int *token_count)
{
	t_token	*tokens;
	t_t2	t2;
	int		capacity;

	capacity = 10;
	t((t2.index = 0, t2.i = 0, t2.j = 0, 0));
	tokens = ft_malloc(sizeof(t_token) * capacity);
	if (!tokens)
		return (NULL);
	while (str[t2.index])
	{
		while (str[t2.index] && is_space(str[t2.index]))
			t2.index++;
		if (!str[t2.index])
			break ;
		if (str[t2.index] == '"' || str[t2.index] == '\'')
			tokenize(str, &t2);
		else
			tokenize2(str, &t2);
		if (t2.j >= capacity && !expand_tokens(&tokens, &capacity))
			return (NULL);
		tokenize3(tokens, &t2);
	}
	*token_count = t2.j;
	return (tokens);
}

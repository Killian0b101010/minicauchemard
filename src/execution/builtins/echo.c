/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:02:44 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/10 18:46:57 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	is_n_flag(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	echo(t_token *tokens, int token_count)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (i < token_count && tokens[i].type == WORD
		&& is_n_flag(tokens[i].value))
	{
		n_flag = 1;
		i++;
	}
	while (i < token_count && tokens[i].type == WORD)
	{
		write(1, tokens[i].value, ft_strlen(tokens[i].value));
		if (i + 1 < token_count && tokens[i + 1].type == WORD)
			write(1, " ", 1);
		i++;
	}
	if (!n_flag)
		write(1, "\n", 1);
	return (0);
}

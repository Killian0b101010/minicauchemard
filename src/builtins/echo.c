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

#include "../../includes/minishell.h"

int	echo(t_token *tokens, int token_count)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (i < token_count && tokens[i].type == WORD
		&& tokens[i].value[0] == '-' && tokens[i].value[1] == 'n'
		&& tokens[i].value[2] == '\0')
	{
		n_flag = 1;
		i++;
	}
	while (i < token_count && tokens[i].type == WORD)
	{
		write(1, tokens[i].value, strlen(tokens[i].value));
		if (i + 1 < token_count)
			write(1, " ", 1);
		i++;
	}
	if (!n_flag)
		write(1, "\n", 1);
	return (0);
}

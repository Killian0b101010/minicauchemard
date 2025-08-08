/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:09:52 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/08 14:19:04 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	t(int a)
{
	(void)a;
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

void	directory_error(char *cmd)
{
	if (cmd[0] == '\0')
		return (write(2, "minicauchemar: Command '' not found\n", 37), (void)0);
	write(2, "minicauchemar: ", 16);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": Is a directory\n", 17);
	g_exit_status = 126;
}

void	print_syntax_error(char *value)
{
	g_exit_status = 2;
	write(2, "minicauchemar: syntax error near unexpected token '", 52);
	write(2, value, ft_strlen(value));
	write(2, "'\n", 2);
}

int	count_pipes(t_token *tokens, int token_count)
{
	int	i;
	int	pipes;

	i = 0;
	pipes = 0;
	while (i < token_count)
	{
		if (tokens[i].type == PIPE)
			pipes++;
		i++;
	}
	return (pipes);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:09:52 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/15 17:41:32 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_cmd_blocks(t_cmd_block *cmds, int block_count)
{
	int	i;

	i = -1;
	while (++i < block_count)
	{
		ft_free_split(cmds[i].args);
		ft_free(cmds[i].tokens);
	}
	ft_free(cmds);
}

char	**build_cmd_args(t_token *tokens, int count)
{
	char	**args;
	int		i;
	int		j;

	args = ft_malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	i = 0;
	j = 0;
	while (i < count)
	{
		if ((tokens[i].type == REDIRECT_IN || tokens[i].type == REDIRECT_OUT
				|| tokens[i].type == APPEND || tokens[i].type == HEREDOC) && i
			+ 1 < count)
		{
			i += 2;
			continue ;
		}
		if (tokens[i].type == WORD)
			args[j++] = ft_strdup(tokens[i].value);
		i++;
	}
	args[j] = NULL;
	return (args);
}

int	is_empty_input(char *input)
{
	int	i;

	if (!input)
		return (1);
	i = 0;
	while (input[i])
	{
		if (!is_space(input[i]))
			return (0);
		i++;
	}
	return (1);
}

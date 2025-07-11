/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:09:52 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/11 17:17:31 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	t(int a)
{
	(void)a;
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

void	*realloc2(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (!ptr)
		return (ft_malloc(new_size));
	if (new_size == 0)
	{
		ft_free(ptr);
		return (NULL);
	}
	new_ptr = ft_malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (old_size < new_size)
		ft_memcpy(new_ptr, ptr, old_size);
	else
		ft_memcpy(new_ptr, ptr, new_size);
	ft_free(ptr);
	return (new_ptr);
}

void	print_syntax_error(char *value)
{
	write(2, "minishell: syntax error near unexpected token '", 48);
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

int	fill_block(t_cmd_block *block, t_token *tokens, int start, int end)
{
	int	k;
	int	count;

	count = end - start;
	block->args = build_cmd_args(&tokens[start], count);
	block->tokens = ft_malloc(sizeof(t_token) * count);
	if (!block->args || !block->tokens)
		return (0);
	k = -1;
	while (++k < count)
	{
		block->tokens[k].value = ft_strdup(tokens[start + k].value);
		block->tokens[k].type = tokens[start + k].type;
		block->tokens[k].quoted = tokens[start + k].quoted;
	}
	return (1);
}

t_cmd_block	*split_into_blocks(t_token *tokens, t_t2 t2, int *block_count)
{
	t_cmd_block	*blocks;
	int			i;
	int			j;
	int			start;

	*block_count = count_pipes(tokens, t2.token_count) + 1;
	blocks = ft_malloc(sizeof(t_cmd_block) * (*block_count));
	if (!blocks)
		return (NULL);
	t((i = 0, j = 0, start = 0, 0));
	while (i <= t2.token_count)
	{
		if (i == t2.token_count || tokens[i].type == PIPE)
		{
			if (!fill_block(&blocks[j], tokens, start, i))
				return (free_cmd_blocks(blocks, j), NULL);
			if (i < t2.token_count)
				tokens[i].value = NULL;
			start = i + 1;
			j++;
		}
		i++;
	}
	return (blocks);
}

void	print_cmd_blocks(t_cmd_block *blocks, int block_count)
{
	int	i;
	int	j;

	i = -1;
	while (++i < block_count)
	{
		printf("📦 Bloc %d:\n", i);
		printf("  Args: ");
		if (!blocks[i].args)
			printf("(none)\n");
		else
		{
			j = -1;
			while (blocks[i].args[++j])
				printf("\"%s\" ", blocks[i].args[j]);
			printf("\n");
		}
		printf("  Tokens: ");
		j = -1;
		while (++j < blocks[i].t2.token_count)
			printf("[%s] ", blocks[i].tokens[j].value);
		printf("\n\n");
	}
}

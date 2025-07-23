/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:00:00 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/15 17:23:39 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <fcntl.h>

static char	*get_heredoc_input(char *delimiter)
{
	char	*input;
	char	*line;
	char	*temp;

	input = ft_strdup("");
	if (!input)
		return (NULL);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			if (line)
				ft_free(line);
			break ;
		}
		temp = ft_strjoin(input, line);
		ft_free(input);
		input = ft_strjoin(temp, "\n");
		ft_free(temp);
		ft_free(line);
	}
	return (input);
}

int	setup_heredoc(char *delimiter)
{
	int		pipe_fd[2];
	char	*input;

	if (pipe(pipe_fd) == -1)
		return (-1);
	input = get_heredoc_input(delimiter);
	if (!input)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	write(pipe_fd[1], input, ft_strlen(input));
	close(pipe_fd[1]);
	ft_free(input);
	return (pipe_fd[0]);
}

static int	handle_redirections(t_token *tokens, int token_count)
{
	int	i;

	i = -1;
	while (++i < token_count)
	{
		if (tokens[i].type == REDIRECT_IN && i + 1 < token_count)
		{
			if (handle_input_redirection(tokens, i) == -1)
				return (-1);
		}
		else if (tokens[i].type == REDIRECT_OUT && i + 1 < token_count)
		{
			if (handle_output_redirection(tokens, i) == -1)
				return (-1);
		}
		else if (tokens[i].type == APPEND && i + 1 < token_count)
		{
			if (handle_append_redirection(tokens, i) == -1)
				return (-1);
		}
		else if (tokens[i].type == HEREDOC && i + 1 < token_count)
			if (handle_heredoc_redirection(tokens, i) == -1)
				return (-1);
	}
	return (0);
}

void	restore_fds(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

int	execute_with_redirections(t_cmd_block *block, t_env *env)
{
	int	saved_stdin;
	int	saved_stdout;
	int	result;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (handle_redirections(block->tokens, block->t2.token_count) == -1)
	{
		restore_fds(saved_stdin, saved_stdout);
		return (1);
	}
	if (is_builtin(block->tokens[0].value))
		result = execute_builtin_block(block, env);
	else
	{
		ft_printf("%s: command not found\n", block->tokens[0].value);
		result = 127;
	}
	restore_fds(saved_stdin, saved_stdout);
	return (result);
}

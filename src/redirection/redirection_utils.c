/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:00:00 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/14 19:03:12 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <fcntl.h>

int	handle_input_redirection(t_token *tokens, int i)
{
	int	fd;

	fd = open(tokens[i + 1].value, O_RDONLY);
	if (fd == -1)
	{
		perror(tokens[i + 1].value);
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	handle_output_redirection(t_token *tokens, int i)
{
	int	fd;

	fd = open(tokens[i + 1].value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(tokens[i + 1].value);
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	handle_append_redirection(t_token *tokens, int i)
{
	int	fd;

	fd = open(tokens[i + 1].value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(tokens[i + 1].value);
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	handle_heredoc_redirection(t_token *tokens, int i)
{
	int	fd;

	fd = setup_heredoc(tokens[i + 1].value);
	if (fd == -1)
		return (-1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

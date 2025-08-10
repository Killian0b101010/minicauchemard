/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:09:52 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/08 18:35:49 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**

 * Construit un tableau d'arguments à partir
 * des tokens en filtrant les redirections.
 *
 * Cette fonction extrait uniquement les mots (WORD) des tokens pour créer
 * un tableau d'arguments exécutable:
 * - Ignore les tokens de redirection et leurs fichiers associés
 * - Ne conserve que les tokens de type WORD
 * - Duplique chaque argument avec ft_strdup()
 * - Termine le tableau par NULL pour compatibilité execve()
 *
 * Parameters :
 * - tokens - Tableau des tokens à analyser
 * - count - Nombre total de tokens
 *
 * Return : Tableau d'arguments terminé par NULL ou NULL si échec
 */
char	**build_cmd_args(t_arena *arena, t_token *tokens, int count)
{
	char	**args;
	int		i;
	int		j;

	args = arena_alloc(arena, (count + 1) * sizeof(char *));
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
			args[j++] = ft_strdup_arena(arena, tokens[i].value);
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

void	close2(int fd)
{
	if (fd >= 2)
		close(fd);
}

void	restore_fds(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close2(saved_stdin);
	close2(saved_stdout);
}

void	ft_error_export(char *var_name)
{
	write(2, "export:", 8);
	write(2, var_name, ft_strlen(var_name));
	write(2, ": not a valid identifier\n", 25);
}

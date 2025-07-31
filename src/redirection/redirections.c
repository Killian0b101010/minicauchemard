/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:00:00 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/31 23:54:15 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <fcntl.h>

/**
 * Lit l'entrée utilisateur pour un heredoc jusqu'au délimiteur spécifié.
 *
 * Cette fonction collecte les lignes d'entrée pour un heredoc (<<)
 * jusqu'à ce que le délimiteur soit rencontré:
 * - Utilise readline() avec un prompt "> "
 * - Concatène chaque ligne avec un retour à la ligne
 * - S'arrête quand le délimiteur exact est trouvé
 * - Gère l'EOF (Ctrl+D) comme fin d'entrée
 *
 * Parameters :
 * - delimiter - Chaîne de délimiteur pour terminer l'entrée
 *
 * Return : Chaîne contenant tout l'input du heredoc ou NULL si erreur
 */
static char	*get_heredoc_input(t_env *env, t_arena *arena, char *delimiter)
{
	char		*input;
	char		*line;
	char		*temp;
	static int	n_line = 0;

	(void)env;
	input = ft_strdup_arena(arena, "");
	if (!input)
		return (NULL);
	while (1)
	{
		n_line++;
		line = readline("heredoc> ");
		if (!line)
		{
			ft_printf("minicauchemar : warning: here-document at line");
			ft_printf(" %d delimited by end-of-file (wanted `%s\')\n", n_line,
				delimiter);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		temp = ft_strjoin_arena(arena, input, line);
		input = ft_strjoin_arena(arena, temp, "\n");
	}
	return (input);
}

/**

 * Configure un pipe pour simuler un heredoc
 * et retourne le descripteur de lecture.
 *
 * Cette fonction met en place l'infrastructure nécessaire pour un heredoc
 * en créant un pipe et en y écrivant l'entrée collectée:
 * - Crée un pipe pour simuler un fichier d'entrée
 * - Collecte l'input du heredoc avec get_heredoc_input()
 * - Écrit l'input dans le pipe
 * - Ferme l'extrémité d'écriture et retourne celle de lecture
 *
 * Parameters :
 * - delimiter - Délimiteur pour terminer l'entrée du heredoc
 *
 * Return : Descripteur de fichier pour la lecture ou -1 si erreur
 */
int	setup_heredoc(t_env *env, t_arena *arena, char *delimiter)
{
	int		pipe_fd[2];
	char	*input;

	if (pipe(pipe_fd) == -1)
		return (-1);
	input = get_heredoc_input(env, arena, delimiter);
	if (!input)
	{
		close2(pipe_fd[0]);
		close2(pipe_fd[1]);
		return (-1);
	}
	write(pipe_fd[1], input, ft_strlen(input));
	close2(pipe_fd[1]);
	return (pipe_fd[0]);
}

/**
 * Traite tous les types de redirections présents dans les tokens.
 *
 * Cette fonction parcourt les tokens pour identifier et configurer
 * toutes les redirections nécessaires:
 * - Gère les redirections d'entrée (<)
 * - Gère les redirections de sortie (>)
 * - Gère les redirections en mode append (>>)
 * - Gère les heredocs (<<)
 * - S'arrête à la première erreur rencontrée
 *
 * Parameters :
 * - tokens - Tableau des tokens à analyser
 * - token_count - Nombre total de tokens
 *
 * Return : 0 en cas de succès, -1 si erreur
 */
int	handle_redirections(t_env *env, t_arena *arena, t_token *tokens,
		int token_count)
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
			if (handle_heredoc_redirection(env, arena, tokens, i) == -1)
				return (-1);
	}
	return (0);
}

void	restore_fds(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close2(saved_stdin);
	close2(saved_stdout);
}

/**
 * Exécute une commande en gérant les redirections et restaure l'état original.
 *
 * Cette fonction coordonne l'exécution d'une commande avec ses redirections
 * tout en préservant l'environnement du shell:
 * - Sauvegarde les descripteurs stdin/stdout originaux
 * - Configure toutes les redirections nécessaires
 * - Exécute la commande (built-in ou externe)
 * - Restaure l'état original des descripteurs
 * - Gère les erreurs de redirection
 *
 * Parameters :
 * - block - Bloc de commande contenant tokens et arguments
 * - env - Structure d'environnement pour l'exécution
 *
 * Return : Code de retour de la commande ou 1 si erreur de redirection
 */

int	execute_with_redirections(t_cmd_block *block, t_env *env)
{
	int	result;
	int	saved_std[2];

	result = 0;
	saved_std[0] = dup(STDIN_FILENO);
	saved_std[1] = dup(STDOUT_FILENO);
	block->is_here_doc = 0;
	if (handle_redirections(env, env->arena, block->tokens,
			block->t2.token_count) == -1)
	{
		block->is_here_doc = 1;
		g_exit_status = 1;
		return (1);
	}
	if (is_builtin(block->tokens[0].value))
		result = execute_builtin_block(block, env);
	else
		execute_cmd_one(block, env);
	restore_fds(saved_std[0], saved_std[1]);
	return (result);
}

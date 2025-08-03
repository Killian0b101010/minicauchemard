/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:00:00 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/03 18:31:48 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**

 * Exécute une commande built-in en identifiant
 * et appelant la fonction appropriée.
 *
 * Cette fonction gère l'exécution des commandes intégrées du shell:
 * - Expanse d'abord les variables $? dans les arguments
 * - Identifie la commande built-in à exécuter
 * - Appelle la fonction correspondante avec les bons paramètres
 * - Met à jour g_exit_status avec le code de retour
 * - Gère le cas spécial de la commande exit
 *
 * Parameters :
 * - block - Bloc de commande contenant la built-in à exécuter
 * - env - Structure d'environnement du shell
 *
 * Return : Code de retour de la commande exécutée
 */
int	execute_builtin_block(t_cmd_block *block, t_env *env)
{
	int	result;

	if (!block->tokens || block->t2.token_count == 0)
		return (1);
	if (ft_strcmp(block->tokens[0].value, "pwd") == 0)
		result = pwd(&block->t2);
	else if (ft_strcmp(block->tokens[0].value, "echo") == 0)
		result = echo(block->tokens, block->t2.token_count);
	else if (ft_strcmp(block->tokens[0].value, "env") == 0)
		result = env_cmd(0, env, block->tokens, &block->t2);
	else if (ft_strcmp(block->tokens[0].value, "cd") == 0)
		result = cd_builtin(block->tokens, block->t2.token_count, env);
	else if (ft_strcmp(block->tokens[0].value, "export") == 0)
		result = export_builtin(env, block->tokens, block->t2.token_count);
	else if (ft_strcmp(block->tokens[0].value, "unset") == 0)
		result = unset(env, block->tokens, block->t2.token_count);
	else if (ft_strcmp(block->tokens[0].value, "exit") == 0)
		return (exit2(env), 0);
	else
		result = 127;
	return (g_exit_status = result, result);
}

// static int	execute_single_block(t_cmd_block *blocks, t_env *env)
// {
// 	int	result;

// 	result = execute_with_redirections(&blocks[0], env);
// 	return (result);
// }

// static int	execute_multiple_blocks(t_cmd_block *blocks, int block_count,
// 		t_env *env)
// {
// 	execute_piped_commands(blocks, block_count, env);
// 	return (1);
// }

void	init_pipes2(int i, t_fd *fd, t_arena *arena)
{
	fd->pipefd = arena_alloc(arena, sizeof(int *) * (fd->cmd_count - 1));
	while (i < fd->cmd_count - 1)
	{
		fd->pipefd[i] = arena_alloc(arena, sizeof(int) * 2);
		pipe(fd->pipefd[i++]);
	}
}

void	init_pipex(t_arena *arena, t_cmd_block *blocks, t_t2 t2, t_fd *fd)
{
	blocks->fd->pid = arena_alloc(arena, sizeof(pid_t) * t2.block_count);
	if (!blocks->fd->pid)
		exit(EXIT_FAILURE);
	init_pipes2(0, fd, arena);
}

void	close_all_fds(t_fd *fd)
{
	int	j;

	j = 0;
	while (j < fd->cmd_count - 1)
	{
		close2(fd->pipefd[j][0]);
		close2(fd->pipefd[j++][1]);
	}
}

void	flagaccesscheck(t_cmd_block *blocks)
{
	if (blocks->flag_access == 0)
	{
		write(2, blocks->args[0], ft_strlen(blocks->args[0]));
		write(2, ": command not found\n", 21);
		exit(127);
	}
}

void	execute_cmd2(t_cmd_block *blocks, t_env *env)
{
	if (!blocks->args[0] && blocks->is_here_doc == 0)
		exit(0);
	if ((!blocks->args || !blocks->args[0]))
		exit((write(2, "Error\n", 7), 1));
	if (!blocks->args || !blocks->args[0])
		exit((write(2, "Error\n", 7), 1));
	blocks->path = get_path_arena(env->arena, env->envp);
	if (!blocks->path)
		exit((if_nopath(blocks->args[0]), 127));
	t((blocks->i = 0, blocks->flag_access = 0, blocks->is_here_doc = 0, 0));
	while (blocks->path[blocks->i])
		exec_loop_one(blocks, env);
	flagaccesscheck(blocks);
	exit(0);
}

void	child_redirection(int i, t_cmd_block *blocks, t_env *env)
{
	int	j;

	j = 0;
	if (i == 0)
	{
		if (blocks->fd->cmd_count > 1)
			dup2(blocks->fd->pipefd[0][1], 1);
	}
	else if (i == blocks->fd->cmd_count - 1)
		dup2(blocks->fd->pipefd[i - 1][0], 0);
	else
		t((dup2(blocks->fd->pipefd[i - 1][0], 0), dup2(blocks->fd->pipefd[i][1],
					1), 0));
	while (j < blocks->fd->cmd_count - 1)
		t((close2(blocks->fd->pipefd[j][0]), close2(blocks->fd->pipefd[j++][1]),
				0));
	blocks[i].is_here_doc = 0;
	if (handle_redirections(env, env->arena, blocks[i].tokens,
			blocks[i].t2.token_count) == -1)
		t((blocks[i].is_here_doc = 1, exit(1), 0));
	if (blocks[i].args[0] && blocks[i].args[0][0])
		execute_cmd2(&blocks[i], env);
	else
		exit(0);
}

pid_t	child_process2(int i, t_cmd_block *blocks, t_env *env)
{
	pid_t	pid;

	if (blocks[i].args[0] && is_builtin(blocks[i].tokens[0].value)
		&& blocks->fd->cmd_count == 1)
	{
		if (ft_strcmp(blocks[i].tokens[0].value, "export") == 0
			|| ft_strcmp(blocks[i].tokens[0].value, "unset") == 0
			|| ft_strcmp(blocks[i].tokens[0].value, "cd") == 0
			|| ft_strcmp(blocks->tokens[0].value, "exit") == 0)
		{
			execute_builtin_block(&blocks[i], env);
			return (-1);
		}
	}
	t((pid = fork(), 0));
	if (pid == 0)
		child_redirection(i, blocks, env);
	return (pid);
}

void	close_unused_pipes(t_fd *fd, int i)
{
	if (i > 0)
	{
		close2(fd->pipefd[i - 1][0]);
		close2(fd->pipefd[i - 1][1]);
	}
}

void	process_commands(t_cmd_block *blocks, t_env *env, int block_count,
		int i)
{
	int	status;

	blocks->fd = arena_alloc(env->arena, sizeof(t_fd));
	if (!blocks->fd)
		return ;
	blocks->fd->cmd_count = block_count;
	blocks->t2.block_count = block_count;
	init_pipex(env->arena, blocks, blocks->t2, blocks->fd);
	while (++i < block_count)
	{
		blocks->fd->pid[i] = child_process2(i, blocks, env);
		close_unused_pipes(blocks->fd, i);
	}
	close_all_fds(blocks->fd);
	i = 0;
	while (i < block_count)
	{
		if (blocks->fd->pid[i] == -1)
			return ;
		waitpid(blocks->fd->pid[i], &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		i++;
	}
}

int	process_input_line(char *input, t_env *env)
{
	t_token		*tokens;
	t_cmd_block	*blocks;
	t_t2		t2;
	int			i;
	int			block_count;

	i = -1;
	t((t2.env_count = 0, t2.pwd_count = 0, 0));
	if (!verify_input(input, t2))
		return (0);
	input = expand_exit_status_in_string(env->arena, input);
	tokens = tokenizer(env->arena, input, &t2.token_count);
	if (!tokens || t2.token_count == 0)
	{
		if (tokens)
			return (1);
	}
	process_token_expansion(tokens, t2.token_count, env);
	blocks = split_into_blocks(env->arena, tokens, t2, &block_count);
	process_commands(blocks, env, block_count, i);
	return (1);
}

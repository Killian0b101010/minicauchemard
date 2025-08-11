/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:32:04 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/11 15:22:15 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	close_all_fds2(void)
{
	int	i;

	i = 0;
	while (i < 1024)
	{
		close2(i);
		i++;
	}
}

/**
 * Implémente la commande built-in exit pour quitter le shell.
 *
 * Cette fonction termine l'exécution du shell de manière propre
 * en appelant exit() avec un code de retour de 0:
 * - Termine immédiatement le processus du shell
 * - Retourne un code de sortie de 0 (succès)
 * - Libère automatiquement toutes les ressources
 * - Reproduit le comportement standard de la commande exit
 *
 * Parameters :
 * - Aucun
 *
 * Return : N/A (la fonction ne retourne jamais)
 */

void	exit2(t_env *env)
{
	close_all_fds2();
	rl_clear_history();
	free_arena(env->arena);
	exit(g_exit_status);
}

int	ft_isstring(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if ((ft_isdigit(str[i])) == 1)
			i++;
		else
			return (1);
	}
	return (0);
}

void	exit_builtin(t_cmd_block *block, t_env *env)
{
	if (block->t2.token_count >= 2)
	{
		if (ft_isstring(block->tokens[1].value) == 1)
		{
			write(2, "minicauchemar: exit: ", 22);
			write(2, block->tokens[1].value, ft_strlen(block->tokens[1].value));
			write(2, ": numeric argument required\n", 29);
			g_exit_status = 2;
			exit2(env);
		}
		else if (ft_isstring(block->tokens[1].value) == 0)
		{
			if (block->t2.token_count == 2)
			{
				g_exit_status = ft_atoi(block->tokens[1].value);
				ft_printf("exit\n");
				exit2(env);
			}
			else
				write(2, "exit\nminicauchemar: exit: too many arguments\n", 46);
		}
	}
	else
		t((write(1, "exit\n", 6), exit2(env), 0));
}

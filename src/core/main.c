/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:40:27 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/03 21:22:36 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <sys/stat.h>
#include <unistd.h>

int			g_exit_status = 0;

/**

 * Initialise l'environnement du shell avec les variables
 * d'environnement et les signaux.
 *
 * Cette fonction configure l'environnement initial du minishell en:
 * - Initialisant les variables d'environnement
 * - Configurant les gestionnaires de signaux
 * - Affichant le message de bienvenue
 *
 * Parameters :
 * - env  - Structure contenant les variables d'environnement
 * - envp - Variables d'environnement du système
 *
 * Return : Aucun (void)
 */

static void	initialize_shell(t_env *env, char **envp)
{
	env->home_path = NULL;
	env->old_path = NULL;
	env->new_path = NULL;
	env->pwd = NULL;
	ft_set_env(env, envp);
	setup_interactive_signals();
	print_minicauchemar();
}

/**
 * Boucle principale du shell qui lit et traite les commandes utilisateur.
 *
 * Parameters : env - Structure contenant les variables d'environnement
 * Return : Aucun (void)
 */
static void	shell_main_loop(t_env *env)
{
	char	**input;
	int		i;

	while (1)
	{
		i = -1;
		input = ft_split_arena(env->arena, get_prompt_and_input(), '\n');
		if (!input)
			exit2(env);
		while (input[++i])
		{
			if (input[i])
				add_history(input[i]);
			if (!process_input_line(input[i], env))
			{
				continue ;
			}
		}
	}
}

int	*is_active_shell(int *bool)
{
	static int	isactive = 0;

	if (bool)
		isactive = *bool;
	return (&isactive);
}

/**
 * Fonction principale qui initialise et exécute le minishell.
 *
 * Cette fonction est le point d'entrée du programme. Elle initialise
 * l'environnement du shell et lance la boucle principale d'exécution.
 *
 * Parameters : ac - Nombre d'arguments (non utilisé)
 *              av - Tableau des arguments (non utilisé)
 *              envp - Variables d'environnement du système
 *
 * Return : 0 en cas de succès
 */

int	main(int ac, char **av, char **envp)
{
	t_env	env;
	t_arena	*arena;

	(void)ac;
	(void)av;
	if (isatty(STDIN_FILENO) == 0)
	{
		write(2,
			"\e[1;38;2;mDose sur tes tests stp et suis plutot la correction\n",
			63);
		return (1);
	}
	arena = arena_init(42);
	if (!arena)
		return (1);
	env.arena = arena;
	initialize_shell(&env, envp);
	shell_main_loop(&env);
	return (0);
}

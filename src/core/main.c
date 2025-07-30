/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:40:27 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/30 23:30:54 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	char	*input;

	while (1)
	{
		input = get_prompt_and_input();
		if (!input)
			break ;
		if (input)
			add_history(input);
		if (!process_input_line(input, env))
		{
			continue ;
		}
	}
}

// t_cmd_block	*heredoc_setter(t_cmd_block *blocks)
// {
// 	static t_cmd_block	*block = NULL;

// 	if (!blocks)
// 		return (block);
// 	else
// 	{
// 		block = blocks;
// 		return (block);
// 	}
// 	return (NULL);
// }

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
	arena = arena_init(64);
	if (!arena)
		return (1);
	env.arena = arena;
	initialize_shell(&env, envp);
	shell_main_loop(&env);
	return (0);
}

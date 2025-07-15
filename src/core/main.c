/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:40:27 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/15 20:32:44 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	initialize_shell(t_env *env, char **envp)
{
	set_env(env, envp);
	setup_interactive_signals();
	print_minicauchemar();
}

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
			ft_free(input);
			continue ;
		}
		ft_free(input);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	env;

	(void)ac;
	(void)av;
	initialize_shell(&env, envp);
	shell_main_loop(&env);
	return (0);
}

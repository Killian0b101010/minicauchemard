/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:40:27 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/14 19:31:46 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	initialize_shell(t_shell *shell, t_env *env, char **envp)
{
	shell->exit_status = 0;
	set_env(env, envp);
	print_minicauchemar();
}

static void	shell_main_loop(t_env *env, t_shell *shell)
{
	char	*input;

	while (1)
	{
		input = get_prompt_and_input();
		if (!input)
			break ;
		if (input)
			add_history(input);
		if (!process_input_line(input, env, shell))
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
	t_shell	shell;

	(void)ac;
	(void)av;
	initialize_shell(&shell, &env, envp);
	shell_main_loop(&env, &shell);
	return (0);
}

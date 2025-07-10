/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:40:27 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/10 18:49:50 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_token	*tokens;
	t_t2	t2;
	t_env	env;
	int		i;

	(void)ac;
	(void)av;
	set_env(&env, envp);
	while (1)
	{
		t2.env_count = 0;
		t2.pwd_count = 0;
		input = readline("minishell> ");
		if (!input)
			break ;
		if (input)
			add_history(input);
		tokens = tokenizer(input, &t2.args);
		if (!tokens)
			ft_free(input);
		i = 0;
		while (i < t2.args)
		{
			if (ft_strcmp(tokens[i].value, "pwd") == 0 && (i == 0 || tokens[i
					- 1].type == PIPE))
				pwd(&t2);
			if (ft_strcmp(tokens[i].value, "echo") == 0 && (i == 0 || tokens[i
					- 1].type == PIPE))
				echo(tokens, t2.args);
			if (ft_strcmp(tokens[i].value, "env") == 0 && (i == 0 || tokens[i
					- 1].type == PIPE))
				env_cmd(i, &env, tokens, &t2);
			i++;
		}
		ft_free(input);
	}
	free_tokens(tokens, t2.args);
	return (0);
}

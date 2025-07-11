/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:40:27 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/11 19:00:26 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	main(int ac, char **av, char **envp)
// {
// 	char		*input;
// 	t_token		*tokens;
// 	t_cmd_block	*blocks;
// 	t_t2		t2;
// 	int			block_count;

// 	(void)ac;
// 	(void)av;
// 	(void)envp;
// 	while (1)
// 	{
// 		t2.token_count = 0;
// 		input = readline("test-block> ");
// 		if (!input)
// 			break ;
// 		if (input[0] != '\0')
// 			add_history(input);
// 		tokens = tokenizer(input, &t2.token_count);
// 		if (!tokens)
// 		{
// 			ft_free(input);
// 			continue ;
// 		}
// 		blocks = split_into_blocks(tokens, t2, &block_count);
// 		if (!blocks)
// 		{
// 			free_tokens(tokens, t2.token_count);
// 			ft_free(input);
// 			continue ;
// 		}
// 		printf("🧮 %d bloc(s) généré(s)\n", block_count);
// 		print_cmd_blocks(blocks, block_count);
// 		free_cmd_blocks(blocks, block_count);
// 		free_tokens(tokens, t2.token_count);
// 		ft_free(input);
// 	}
// 	return (0);
// }

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_token	*tokens;
	t_t2	t2;
	t_env	env;
	int		i;
	char	cwd[10000];
	char	*prompt;

	(void)ac;
	(void)av;
	set_env(&env, envp);
	while (1)
	{
		t2.env_count = 0;
		t2.pwd_count = 0;
		getcwd(cwd, sizeof(cwd));
		prompt = ft_strjoin("minicauchemar:", cwd);
		prompt = ft_strjoin(prompt, "$ ");
		input = readline(prompt);
		if (!input)
			break ;
		if (input)
			add_history(input);
		tokens = tokenizer(input, &t2.token_count);
		if (!tokens)
		{
			ft_free(input);
			continue ;
		}
		i = 0;
		while (i < t2.token_count)
		{
			if (ft_strcmp(tokens[i].value, "pwd") == 0 && (i == 0 || tokens[i
					- 1].type == PIPE))
				pwd(&t2);
			if (ft_strcmp(tokens[i].value, "echo") == 0 && (i == 0 || tokens[i
					- 1].type == PIPE))
				echo(tokens, t2.token_count);
			if (ft_strcmp(tokens[i].value, "env") == 0 && (i == 0 || tokens[i
					- 1].type == PIPE))
				env_cmd(i, &env, tokens, &t2);
			if (ft_strcmp(tokens[i].value, "cd") == 0 && (i == 0 || tokens[i
					- 1].type == PIPE))
				cd_builtin(&tokens[i], t2.token_count - i, &env);
			i++;
		}
		ft_free(input);
	}
	free_tokens(tokens, t2.token_count);
	return (0);
}

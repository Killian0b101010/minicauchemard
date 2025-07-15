/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:00:00 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/15 21:03:51 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_minicauchemar(void)
{
	ft_printf(" ___  ____       _                      _");
	ft_printf("                               \n");
	ft_printf("|  \\/  (_)     (_)                 ");
	ft_printf("   | |                              \n");
	ft_printf("| .  . |_ _ __  _  ___ __ _ _   _  _");
	ft_printf("__| |__   ___ _ __ ___   __ _ _ __ \n");
	ft_printf("| |\\/| | | '_ \\| |/ __/ _` | | | |/");
	ft_printf(" __| '_ \\ / _ \\ '_ ` _ \\ / _` | '__|\n");
	ft_printf("| |  | | | | | | | (_| (_| | |_| | (__|");
	ft_printf(" | | |  __/ | | | | | (_| | |   \n");
	ft_printf("\\_|  |_/_|_| |_|_|\\___\\__,_|\\__,_|\\_");
	ft_printf("__|_| |_|\\___|_| |_| |_|\\__,_|_|  \n");
}

char	*get_prompt_and_input(void)
{
	char	cwd[10000];
	char	*prompt;
	char	*input;

	getcwd(cwd, sizeof(cwd));
	prompt = ft_strjoin("minicauchemar:", cwd);
	prompt = ft_strjoin(prompt, "$ ");
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, ft_handler2);
	input = readline(prompt);
	ft_free(prompt);
	return (input);
}

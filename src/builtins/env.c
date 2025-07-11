/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:41:04 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/11 23:34:21 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_env(t_env *env, char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (envp[i])
		i++;
	env->envp = ft_malloc(sizeof(char *) * (i + 1));
	if (!env->envp)
		return ;
	while (++j < i)
		env->envp[j] = ft_strdup(envp[j]);
}

int	env_cmd(int index, t_env *env, t_token *tokens, t_t2 *t2)
{
	int	i;

	i = 0;
	if (t2->token_count > index + 1 && tokens[index + 1].type == WORD)
	{
		write(2, "env: \'", 7);
		write(2, tokens[index + 1].value, ft_strlen(tokens[index + 1].value));
		write(2, "\': No such file or directory\n", 30);
		return (1);
	}
	else if (t2->env_count == 0)
	{
		while (env->envp[i])
		{
			ft_printf("%s\n", env->envp[i]);
			i++;
		}
		t2->env_count = 1;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:56:08 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/11 16:23:25 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*set_env_value(t_env *env, const char *key, char *buffer)
{
	char	*new_path;
	char	buffer[BUFFER_SIZE];

	while (env->envp)
	{
		if (ft_strncmp(env->envp, key, 4) == 0)
		{
			free(env->envp);
			set_env(env, env->envp);
		}
		else
			getcwd(buffer, BUFFER_SIZE);
	}
	return (env->envp);
}

void	cd_bulltins_two(t_env *env)
{
	char		*target;
	char		buffer[BUFFER_SIZE];
	struct stat	st;

	if (target && stat(target, &st) == 0 && S_ISDIR(st.st_mode))
	{
		if (chdir(target) != 0)
			return (perror("cd"), 1);
		if (getcwd(buffer, BUFFER_SIZE))
			set_env_value(env, "PWD", buffer);
		return (0);
	}
}

int	cd_builtin(t_token *tokens, int token_count, t_env *env)
{
	char		buffer[BUFFER_SIZE];
	char		*home;
	struct stat	st;
	char		*target;

	home = getenv("HOME");
	if (!home)
		return (fprintf(stderr, "cd : HOME not set\n"), 1);
	// cd sans argument ou cd ~
	if (token_count == 1 || (token_count >= 2 && ft_strcmp(tokens[1].value,
				"~") == 0))
		target = home;
	else if (token_count >= 2)
		target = tokens[1].value;
	if (token_count > 2)
		return (ft_printf("cd : too many arguments\n"), 1);
	// sauvegarde de l'ancien PWD
	if (getcwd(buffer, BUFFER_SIZE))
		set_env_value(env, "OLDPWD", buffer);
	// verifie si le chemin est un dossier valide
	cd_bulltins_two(env);
	return (write(stderr, "Not a directory", 16), 1);
}

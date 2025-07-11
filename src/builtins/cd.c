/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:56:08 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/11 17:32:12 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*set_env_value(t_env *env, const char *key)
{
	//fonction non finis
	char	*new_key;
	char	*new_path;
	char	cwd[BUFFER_SIZE];
	int		i;

	i = 0;
	if (!getcwd(cwd, BUFFER_SIZE))
		return (NULL);
	// Creation du path soit old soit PWD?
	new_key = ft_strjoin(key, "=");
	if (!new_key)
		return (NULL);
	new_path = ft_strjoin(new_key, cwd);
	free(new_key);
	if (!new_path)
		return (NULL);
	while (env->envp[i])
	{
		// si pwd
		if (ft_strncmp(env->envp[i], key, ft_strlen(key)) == 0
			&& env->envp[i][ft_strlen(key)] == '=')
		{
			free(env->envp[i]);
			env->envp[i] = new_path;
			return (new_path);
		}
		i++;
	}
	return (NULL);
}

static void	cd_bulltins_two(t_env *env, char *target)
{
	char		buffer[BUFFER_SIZE];
	struct stat	st;

	if (target && stat(target, &st) == 0 && S_ISDIR(st.st_mode))
	{
		if (chdir(target) != 0)
		{
			perror("cd");
			return ;
		}
		if (getcwd(buffer, BUFFER_SIZE))
			set_env_value(env, "PWD");
		return ;
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
		set_env_value(env, "OLDPWD");
	// verifie si le chemin est un dossier valide
	if (target && stat(target, &st) == 0 && S_ISDIR(st.st_mode))
	{
		cd_bulltins_two(env, target);
		return (0);
	}
	return (write(2, "Not a directory", 16), 1);
}

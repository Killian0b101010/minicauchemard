/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:56:08 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/01 17:02:41 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*set_env_value(t_env *env, char *key)
{
	char	*new_key;
	char	*new_path;
	char	cwd[BUFFER_SIZE_CD];
	int		i;

	i = -1;
	if (!getcwd(cwd, BUFFER_SIZE_CD))
		return (NULL);
	new_key = ft_strjoin_arena(env->arena, key, "=");
	if (!new_key)
		return (NULL);
	new_path = ft_strjoin_arena(env->arena, new_key, cwd);
	if (!new_path)
		return (NULL);
	while (env->envp[++i])
	{
		if (ft_strncmp(env->envp[i], key, ft_strlen(key)) == 0
			&& env->envp[i][ft_strlen(key)] == '=')
			return (env->envp[i] = new_path, new_path);
	}
	return (NULL);
}

static void	cd_bulltins_two(t_env *env, char *target)
{
	char		buffer[BUFFER_SIZE_CD];
	struct stat	st;

	if (target && stat(target, &st) == 0 && S_ISDIR(st.st_mode))
	{
		if (chdir(target) != 0)
		{
			perror("cd");
			return ;
		}
		if (getcwd(buffer, BUFFER_SIZE_CD))
			set_env_value(env, "PWD");
		return ;
	}
}

int	cd_builtin(t_token *tokens, int token_count, t_env *env)
{
	char		buffer[BUFFER_SIZE_CD];
	char		*home;
	struct stat	st;
	char		*target;

	home = getenv("HOME");
	if (token_count == 1 || (token_count >= 2 && ft_strcmp(tokens[1].value,
				"~") == 0) || (token_count >= 2 && ft_strcmp(tokens[1].value,
				"--") == 0))
	{
		if (!home)
			return (write(2, "cd : HOME not set \n", 19), g_exit_status = 1);
		target = home;
	}
	else if (token_count == 2)
		target = tokens[1].value;
	if (token_count > 2)
		return (ft_printf("cd : too many arguments\n"), 1);
	if (getcwd(buffer, BUFFER_SIZE_CD))
		set_env_value(env, "OLDPWD");
	if (target && stat(target, &st) == 0 && S_ISDIR(st.st_mode))
		return (cd_bulltins_two(env, target), 0);
	return (write(2, "cd: no such file or directory: \n", 33), 1);
}

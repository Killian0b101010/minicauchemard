/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:56:08 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/10 22:17:52 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cd(int ac, char **argv, t_cd *env)
{
	home = getenv("HOME");
	chdir(home);
}

char	*set_env_value(t_envv *env, const char *key, const char *value)
{
	while (env->envp)
	{
	}
}
int	cd(int ac, char **argv, t_envv *env)
{
	char		buffer[BUFFER_SIZE];
	char		*home;
	struct stat	st;

	home = getenv("HOME");
	// Plusieurs args
	if (ac > 2)
		return (fprintf(stderr, "cd : too many arguments"), 1);
	// Ancien pwd
	env->old_path = getenv("PWD");
	// Si sa echoue
	if (!home)
		return (fprintf(stderr, "cd : HOME not set"), 1);
	// direct le home
	if (ac == 1)
		go_home(home);
	// si cd ~
	if (ac == 2 && ft_strcmp(argv[1], "~") == 0)
		return (go_home(home), 0);
	// execute cd + dossier et verifie que c bien un directory
	if (ac == 2)
	{
		if (stat(argv[1], &st) == 0 && S_ISDIR(st.st_mode))
		{
			chdir(argv[1]);
			getcwd(buffer, BUFFER_SIZE);
			env->pwd = ft_strdup(buffer);
			return (0);
		}
		return (write(stderr, "Not a directory", 16), 1);
	}
}

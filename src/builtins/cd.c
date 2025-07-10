/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:56:08 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/10 13:32:21 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cd(int ac, char **argv, t_cd *env)
{
	if (ac > 2)
		return (fprintf(stderr, "cd : too many arguments"), 1);
	if (ac == 1)
		env->home_path = getenv("HOME");
	if (!env->home_path)
		return (fprintf(stderr, "cd : HOME not set"), 1);
	env->old_path = getenv("PWD");
	chdir(env->home_path);
	get_cwd(env->new_path);
	else if (ac == 2)
	{
	}
}

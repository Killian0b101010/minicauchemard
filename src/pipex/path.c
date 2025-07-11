/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:44:19 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/10 17:59:09 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

int	is_abs_path(char *cmd)
{
	return ((ft_strncmp(&cmd[0], "/", 1)) == 0);
}

char	**get_path(char **envp)
{
	ssize_t	i;
	char	**path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_split(envp[i] + 5, ':');
			if (!path)
				return (NULL);
			return (path);
		}
		i++;
	}
	i = 0;
	return (NULL);
}

char	*get_absolute_path(char *cmd, char *path)
{
	char	*full_cmd;

	if (ft_strchr(cmd, '/'))
	{
		full_cmd = ft_strdup(cmd);
		return (full_cmd);
	}
	full_cmd = ft_strjoin(path, "/");
	full_cmd = ft_strjoin(path, cmd);
	return (full_cmd);
}

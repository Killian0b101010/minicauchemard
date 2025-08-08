/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:44:19 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/07 18:33:46 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_abs_path(char *cmd)
{
	return (((ft_strncmp(&cmd[0], "/", 1)) == 0) || ((ft_strncmp(&cmd[0], "./",
					2)) == 0));
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

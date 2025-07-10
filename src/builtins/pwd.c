/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:26:17 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/10 17:32:02 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd(t_t2 *t2)
{
	char	cwd[10000];

	if (getcwd(cwd, sizeof(cwd)))
	{
		if (t2->pwd_count == 0)
		{
			ft_printf("%s\n", cwd);
			t2->pwd_count = 1;
		}
	}
	else
		perror("getcwd");
	return (0);
}

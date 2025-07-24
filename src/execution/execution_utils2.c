/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:46:10 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/24 18:50:33 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	verify_input(char *input, t_t2 t2)
{
	if (is_empty_input(input))
		return (0);
	if (!count_quotes(input, &t2.single_quotes, &t2.double_quotes))
		return (0);
	return (1);
}

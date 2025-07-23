/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:08:52 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/23 17:09:42 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	ft_free(s1);
	return (joined);
}

char	*join_itoa_free(char *str, int num)
{
	char	*num_str;
	char	*result;

	num_str = ft_itoa(num);
	result = ft_strjoin_free(str, num_str);
	ft_free(num_str);
	return (result);
}

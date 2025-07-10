/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:49:30 by dnahon            #+#    #+#             */
/*   Updated: 2025/04/28 16:31:18 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strstr(const char *str, const char *to_find)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (to_find[i] == '\0')
		return ((char *)str);
	while (str[i])
	{
		j = 0;
		while (str[i + j] == to_find[j])
		{
			if (to_find[j + 1] == '\0')
				return ((char *)str + i);
			j++;
		}
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	const char	*str = "Hello, World!";
	const char	*to_find = "World";
	char		*result;

	result = ft_strstr(str, to_find);
	if (result)
	{
		printf("Found: %s\n", result);
	}
	else
	{
		printf("Not found\n");
	}
	return (0);
}
 */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:11:26 by dnahon            #+#    #+#             */
/*   Updated: 2025/04/29 13:32:00 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (to_find[i] == '\0')
		return ((char *)str);
	while (str[i] && i < len)
	{
		j = 0;
		while (str[i + j] == to_find[j] && i + j < len)
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
#include <stdio.h>

int	main(void)
{
	const char	*str = "Hello, World!";
	const char	*to_find = "World";
	size_t		len;
	char		*result;

	len = 20;
	result = ft_strnstr(str, to_find, len);
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
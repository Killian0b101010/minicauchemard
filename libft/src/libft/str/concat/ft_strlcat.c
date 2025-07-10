/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:37:33 by dnahon            #+#    #+#             */
/*   Updated: 2025/05/15 14:17:02 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/libft.h"
#include <stddef.h>

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	dest_len = (size_t)ft_strlen(dest);
	src_len = (size_t)ft_strlen(src);
	if (size <= dest_len)
		return (size + src_len);
	i = 0;
	while (src[i] != '\0' && dest_len + i < size - 1)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}
/*
int	main(void)
{
	char		dest[50] = "Hello, ";
	const char	*src = "World!";
	size_t		size;

	size = 20;
	printf("Before strlcat: %s\n", dest);
	ft_strlcat(dest, src, size);
	printf("After strlcat: %s\n", dest);
	return (0);
}
 */
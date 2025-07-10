/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:58:37 by dnahon            #+#    #+#             */
/*   Updated: 2025/04/30 18:16:31 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s = src;

	if (!dest && !src)
		return (NULL);
	d = dest;
	while (n--)
		*d++ = *s++;
	return (dest);
}
/*
int	main(void)
{
	char	src[] = "Hello, World!";
	char	dest[20];

	ft_memcpy(dest, src, 5);
	dest[5] = '\0';
	return (0);
}
 */
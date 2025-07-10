/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:28:51 by dnahon            #+#    #+#             */
/*   Updated: 2025/05/15 14:17:02 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/libft.h"

char	*ft_strdup(const char *src)
{
	char	*ptr;

	ptr = (char *)ft_malloc(sizeof(char) * ft_strlen(src) + 1);
	if (!ptr)
		return (NULL);
	ptr = ft_strcpy(ptr, src);
	return (ptr);
}
/*
int	main(void)
{
	const char	*src = "Hello, World!";
	char		*dup;

	dup = ft_strdup(src);
	if (!dup)
		return (1);
	printf("Original: %s\n", src);
	printf("Duplicate: %s\n", dup);
	ft_free(dup);
	return (0);
}
 */
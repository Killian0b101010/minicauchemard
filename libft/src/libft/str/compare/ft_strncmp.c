/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:40:50 by dnahon            #+#    #+#             */
/*   Updated: 2025/04/28 16:27:47 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char	str1[] = "Hello";
	char	str2[] = "Hello";
	char	str3[] = "World";

	printf("Comparing '%s' and '%s': %d\n", str1, str2, ft_strncmp(str1, str2,
			5));
	printf("Comparing '%s' and '%s': %d\n", str1, str3, ft_strncmp(str1, str3,
			5));
	printf("Comparing '%s' and '%s': %d\n", str3, str2, ft_strncmp(str3, str2,
			5));
	return (0);
}
 */
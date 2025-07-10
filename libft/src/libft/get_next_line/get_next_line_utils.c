/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:21:49 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/06 22:12:55 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/get_next_line.h"

size_t	ft_strlen2(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr3(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	str = malloc(ft_strlen2(s1) + ft_strlen2(s2) + 1);
	if (!str)
		return (free(s1), NULL);
	i = 0;
	j = 0;
	if (s1)
	{
		while (s1[i])
			str[j++] = s1[i++];
	}
	i = 0;
	if (s2)
	{
		while (s2[i])
			str[j++] = s2[i++];
	}
	str[j] = '\0';
	free(s1);
	return (str);
}

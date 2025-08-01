/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_arena.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:07:26 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/01 19:07:58 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin_arena(t_arena *arena, char *s1, char *s2)
{
	char			*str;
	unsigned int	i;
	unsigned int	j;

	free((i = 0, j = 0, NULL));
	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup_arena(arena, s2));
	else if (!s2)
		return (ft_strdup_arena(arena, s1));
	str = arena_alloc(arena, ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	while (s1[i])
		t((str[i] = s1[i], i++, 0));
	while (s2[j])
		t((str[i + j] = s2[j], j++, 0));
	str[i + j] = '\0';
	return (str);
}

static size_t	ft_nblen(int n)
{
	int	len;

	len = (n <= 0);
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa_arena(t_arena *arena, int n)
{
	long	nb;
	int		len;
	char	*str;

	nb = n;
	len = ft_nblen(n);
	str = arena_alloc(arena, len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	while (len-- > (n < 0))
	{
		str[len] = (nb % 10) + '0';
		nb = nb / 10;
	}
	return (str);
}

void	*ft_realloc_arena(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (old_size > new_size)
		old_size = new_size;
	ft_memcpy(new_ptr, ptr, old_size);
	free(ptr);
	return (new_ptr);
}

char	**get_path_arena(t_arena *arena, char **envp)
{
	ssize_t	i;
	char	**path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_split_arena(arena, envp[i] + 5, ':');
			if (!path)
				return (NULL);
			return (path);
		}
		i++;
	}
	i = 0;
	return (NULL);
}

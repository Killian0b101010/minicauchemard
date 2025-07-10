/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:08:05 by dnahon            #+#    #+#             */
/*   Updated: 2025/05/15 14:17:02 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/libft.h"

static int	count_words(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static char	*malloc_word(char const *s, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	word = (char *)ft_malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, s, i + 1);
	return (word);
}

static void	*free_all(char **tab, int j)
{
	while (j >= 0)
	{
		ft_free(tab[j]);
		j--;
	}
	ft_free(tab);
	return (NULL);
}

static char	**ft_minisplit(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tab = (char **)ft_malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!tab)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			tab[j] = malloc_word(&s[i], c);
			if (!tab[j++])
				return (free_all(tab, j - 1));
		}
		while (s[i] && s[i] != c)
			i++;
	}
	tab[j] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = ft_minisplit(s, c);
	return (tab);
}
/*
int	main(void)
{
	char	**result;
	int		i;

	result = ft_split("Hello, World! This is a test.", ' ');
	if (!result)
	{
		printf("Memory allocation failed\n");
		return (1);
	}
	i = 0;
	while (result[i])
	{
		printf("%s\n", result[i]);
		ft_free(result[i]);
		i++;
	}
	ft_free(result);
	return (0);
}
 */
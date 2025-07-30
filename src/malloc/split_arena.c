
#include "../../includes/minishell.h"

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

static char	*malloc_word(t_arena *arena, const char *s, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	word = arena_alloc(arena, i + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, s, i + 1);
	return (word);
}


static char	**ft_minisplit(t_arena *arena, char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tab = arena_alloc(arena, (count_words(s, c) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			tab[j] = malloc_word(arena, &s[i], c);
			if (!tab[j])
				return(NULL);
            j++;
		}
		while (s[i] && s[i] != c)
			i++;
	}
	tab[j] = NULL;
	return (tab);
}

char	**ft_split_arena(t_arena *arena, char const *s, char c)
{
	char **tab;

	if (!s)
		return (NULL);
	tab = ft_minisplit(arena, s, c);
	return (tab);
}

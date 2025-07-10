/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:32:52 by dnahon            #+#    #+#             */
/*   Updated: 2025/05/15 13:49:45 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (unsigned char)c)
			return ((char *)str);
		str++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)str);
	return (0);
}
/*
int	main(void)
{
	const char	*str = "Hello, World!";
	int			c;
	char		*result;

	c = 'W';
	result = ft_strchr(str, c);
	if (result)
	{
		printf("Character '%c' found at position: %ld\n", c, result - str);
	}
	else
	{
		printf("Character '%c' not found.\n", c);
	}
	return (0);
}
 */
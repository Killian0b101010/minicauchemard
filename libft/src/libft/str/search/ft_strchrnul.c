/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrnul.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:10:32 by dnahon            #+#    #+#             */
/*   Updated: 2025/04/28 16:30:54 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchrnul(const char *str, int c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	while (*str)
	{
		if (*str == uc)
			return ((char *)str);
		str++;
	}
	return ((char *)str);
}
/*
int	main(void)
{
	const char	*str = "Hello, World!";
	int			c;
	char		*result;

	c = 'W';
	result = ft_strchrnul(str, c);
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
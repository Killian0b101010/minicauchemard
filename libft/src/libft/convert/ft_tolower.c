/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:28:27 by dnahon            #+#    #+#             */
/*   Updated: 2025/04/28 16:23:18 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
/*
int	main(void)
{
	int		c;
	char	*str;

	c = 'A';
	str = "HELLO";
	printf("%c\n", ft_tolower(c));
	printf("%s\n", str);
	return (0);
}
 */
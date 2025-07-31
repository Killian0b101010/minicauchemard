/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:34:51 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/30 03:42:31 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

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

char	*ft_itoa(int n)
{
	long	nb;
	int		len;
	char	*str;

	nb = n;
	len = ft_nblen(n);
	str = ft_malloc(sizeof(char) * len + 1);
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
/*
int	main(void)
{
	int		num;
	char	*str;

	num = -12345;
	str = ft_itoa(num);
	if (str)
	{
		printf("Integer: %d\n", num);
		printf("String: %s\n", str);
		free(str);
	}
	else
	{
		printf("Memory allocation failed\n");
	}
	return (0);
}
 */
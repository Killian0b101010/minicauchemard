/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbrui.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:48:37 by dnahon            #+#    #+#             */
/*   Updated: 2025/05/15 14:17:55 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_printf.h"

static size_t	ft_nblen(unsigned int n)
{
	int	len;

	len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*ft_uitoa(unsigned int n)
{
	long	nb;
	int		len;
	char	*str;

	nb = n;
	len = ft_nblen(n);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len-- > (n < 0))
	{
		str[len] = (nb % 10) + '0';
		nb = nb / 10;
	}
	return (str);
}

int	ft_printnbrui(unsigned int n)
{
	int		len;
	char	*num;

	len = 0;
	if (n == 0)
		len += write(1, "0", 1);
	else
	{
		num = ft_uitoa(n);
		len += ft_printstr(num);
		free(num);
	}
	return (len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:58:03 by dnahon            #+#    #+#             */
/*   Updated: 2025/05/15 14:17:55 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_printf.h"

static int	ft_ptrlen(uintptr_t ptr)
{
	int	len;

	len = 0;
	while (ptr != 0)
	{
		len++;
		ptr /= 16;
	}
	return (len);
}

static void	ft_putptr(uintptr_t ptr)
{
	char	*hex_base;
	char	buffer[16];
	int		i;

	if (!ptr)
		return ;
	hex_base = "0123456789abcdef";
	write(1, "0x", 2);
	i = 0;
	while (ptr > 0)
	{
		buffer[i++] = hex_base[ptr % 16];
		ptr /= 16;
	}
	while (--i >= 0)
		write(1, &buffer[i], 1);
}

int	ft_printptr(unsigned long long ptr)
{
	int	printed_chars;

	if (ptr == 0)
		return (write(1, "(nil)", 5));
	printed_chars = 2;
	ft_putptr(ptr);
	printed_chars += ft_ptrlen(ptr);
	return (printed_chars);
}

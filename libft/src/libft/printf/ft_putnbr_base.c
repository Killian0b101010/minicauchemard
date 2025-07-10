/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:09:36 by dnahon            #+#    #+#             */
/*   Updated: 2025/05/16 12:41:57 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/ft_printf.h"

static int	ft_hexlen(unsigned int nbr)
{
	int	len;

	len = 0;
	while (nbr)
	{
		len++;
		nbr /= 16;
	}
	return (len);
}

static void	ft_putnbr_base_upperx(unsigned int nbr)
{
	unsigned int	base_len;
	char			*base;

	base = "0123456789ABCDEF";
	if (!is_valid_base(base))
		return ;
	base_len = 0;
	while (base[base_len])
		base_len++;
	if (nbr >= base_len)
		ft_putnbr_base_upperx(nbr / base_len);
	ft_printchar(base[nbr % base_len]);
}

static void	ft_putnbr_base_lowerx(unsigned int nbr)
{
	unsigned int	base_len;
	char			*base;

	base = "0123456789abcdef";
	if (!is_valid_base(base))
		return ;
	base_len = 0;
	while (base[base_len])
		base_len++;
	if (nbr >= base_len)
		ft_putnbr_base_lowerx(nbr / base_len);
	ft_printchar(base[nbr % base_len]);
}

int	ft_print_upperhex(unsigned int nbr)
{
	if (nbr == 0)
		return (write(1, "0", 1));
	else
		ft_putnbr_base_upperx(nbr);
	return (ft_hexlen(nbr));
}

int	ft_print_lowerhex(unsigned int nbr)
{
	if (nbr == 0)
		return (write(1, "0", 1));
	else
		ft_putnbr_base_lowerx(nbr);
	return (ft_hexlen(nbr));
}

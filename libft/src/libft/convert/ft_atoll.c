/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 23:54:15 by dnahon            #+#    #+#             */
/*   Updated: 2025/04/28 16:22:49 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long	ft_atoll(const char *str)
{
	long long	nb;
	int			i;
	int			signe;

	nb = 0;
	i = 0;
	signe = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb * signe);
}
/*
int	main(void)
{
	const char	*str = "  -1234567890123456789";
	long long	result;

	result = ft_atoll(str);
	printf("Result: %lld\n", result); // Expected output: -1234567890123456789
	return (0);
}
 */
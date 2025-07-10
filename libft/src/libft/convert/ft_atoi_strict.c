/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_strict.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 23:55:40 by dnahon            #+#    #+#             */
/*   Updated: 2025/04/28 16:21:48 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi_strict(const char *str)
{
	int	nb;
	int	i;
	int	signe;

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
	if (str[i] != '\0')
		return (0);
	return (nb * signe);
}
/*
int	main(void)
{
	const char	*str = "  -12345";
	int			result;

	result = ft_atoi_strict(str);
	printf("Result: %d\n", result); // Expected output: -12345
	return (0);
}
 */
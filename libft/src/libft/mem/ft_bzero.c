/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:56:14 by dnahon            #+#    #+#             */
/*   Updated: 2025/06/06 16:14:20 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
/*
int	main(void)
{
	char	str[50];

	ft_strcpy(str, "Hello, World!");
	printf("Before ft_bzero: %s\n", str);
	ft_bzero(str, 5);
	printf("After ft_bzero: %s\n", str);
	return (0);
}
 */
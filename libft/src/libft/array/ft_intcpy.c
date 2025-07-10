/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:23:14 by dnahon            #+#    #+#             */
/*   Updated: 2025/04/28 16:19:29 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	*ft_intcpy(int *src, int *dst, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

/* int main(void)
{
	int src[5] = {1, 2, 3, 4, 5};
	int dst[5];
	int i;

	ft_intcpy(src, dst, 5);
	for (i = 0; i < 5; i++)
		printf("%d ", dst[i]);
	return (0);
} */

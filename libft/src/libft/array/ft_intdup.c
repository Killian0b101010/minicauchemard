/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:30:18 by dnahon            #+#    #+#             */
/*   Updated: 2025/06/06 16:13:17 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"
#include <stddef.h>

int	*ft_arrdup(int *arr, size_t size)
{
	int	*dup;

	dup = (int *)ft_malloc(sizeof(int) * size);
	if (!dup)
		return (NULL);
	dup = ft_intcpy(arr, dup, size);
	return (dup);
}

/* int main(void)
{
	int arr[5] = {1, 2, 3, 4, 5};
	int *dup;
	size_t i;

	dup = ft_arrdup(arr, 5);
	if (!dup)
		return (1);
	for (i = 0; i < 5; i++)
		printf("%d ", dup[i]);
	ft_free(dup);
	return (0);
} */

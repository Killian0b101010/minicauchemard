/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 23:53:09 by dnahon            #+#    #+#             */
/*   Updated: 2025/04/28 16:18:09 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
}

/* int	main(void)
{
	int	*ptr;
	int	i;

	ptr = (int *)ft_malloc(5 * sizeof(int));
	if (!ptr)
		return (1);
	for (i = 0; i < 5; i++)
		ptr[i] = i;
	for (i = 0; i < 5; i++)
		printf("%d ", ptr[i]);
	ft_free(ptr);
	return (0);
} */

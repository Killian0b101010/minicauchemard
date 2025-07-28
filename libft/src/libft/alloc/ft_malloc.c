/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 23:46:44 by dnahon            #+#    #+#             */
/*   Updated: 2025/07/27 20:14:42 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"
#include <stddef.h>
#include <stdlib.h>

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_putstr_fd("Malloc failed\n", 2);
		return (NULL);
	}
	return (ptr);
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

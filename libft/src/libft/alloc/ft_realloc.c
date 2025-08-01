/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 23:56:31 by dnahon            #+#    #+#             */
/*   Updated: 2025/08/01 18:59:30 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"
#include <stddef.h>

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (!ptr)
		return (ft_malloc(size));
	if (size == 0)
	{
		ft_free(ptr);
		return (NULL);
	}
	new_ptr = ft_malloc(size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, size);
	ft_free(ptr);
	return (new_ptr);
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
	ptr = realloc(ptr, 10 * sizeof(int));
	if (!ptr)
		return (1);
	for (i = 0; i < 10; i++)
		printf("%d ", ptr[i]);
	ft_free(ptr);
	return (0);
} */

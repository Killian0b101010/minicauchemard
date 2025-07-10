/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:06:35 by dnahon            #+#    #+#             */
/*   Updated: 2025/06/06 16:13:10 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb && size > SIZE_MAX / nmemb)
		return (NULL);
	ptr = ft_malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, nmemb * size);
	return (ptr);
}

/* int	main(void)
{
	int	*ptr;
	int	i;

	ptr = (int *)ft_calloc(5, sizeof(int));
	if (!ptr)
		return (1);
	for (i = 0; i < 5; i++)
		printf("%d ", ptr[i]);
	ft_free(ptr);
	return (0);
} */

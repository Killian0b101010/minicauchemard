/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:34:50 by dnahon            #+#    #+#             */
/*   Updated: 2025/06/06 16:14:08 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
}
/*
int	main(void)
{
	t_list	*lst;
	t_list	*new;

	lst = ft_lstnew("Hello");
	new = ft_lstnew("World");
	lst->next = new;
	ft_lstclear(&lst, ft_free);
	if (lst == NULL)
		printf("List cleared successfully\n");
	else
		printf("List not cleared\n");
	return (0);
}
*/
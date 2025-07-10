/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:26:04 by dnahon            #+#    #+#             */
/*   Updated: 2025/06/06 16:14:05 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	if (lst->content)
		del(lst->content);
	ft_free(lst);
}
/*
int	main(void)
{
	t_list	*lst;
	t_list	*new;

	lst = ft_lstnew("Hello");
	new = ft_lstnew("World");
	lst->next = new;
	ft_lstdelone(lst, ft_free);
	return (0);
}
 */
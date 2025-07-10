/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnahon <dnahon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:08:46 by dnahon            #+#    #+#             */
/*   Updated: 2025/06/06 16:13:32 by dnahon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	while (*lst)
		lst = &(*lst)->next;
	*lst = new;
}
/*
int	main(void)
{
	t_list	*lst;
	t_list	*new;

	lst = ft_lstnew("Hello");
	new = ft_lstnew("World");
	ft_lstadd_back(&lst, new);
	printf("%s\n", (char *)lst->content);
	printf("%s\n", (char *)lst->next->content);
	return (0);
}
 */
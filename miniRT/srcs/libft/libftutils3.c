/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftutils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesvall <adesvall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:25:03 by adesvall          #+#    #+#             */
/*   Updated: 2021/01/26 19:30:01 by adesvall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int		ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*elem;

	elem = malloc(sizeof(t_list));
	if (elem == 0)
		return (0);
	elem->content = content;
	elem->next = 0;
	return (elem);
}

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst)
		return ;
	if (del)
		(*del)(lst->content);
	free(lst);
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*cur;

	cur = *lst;
	while (cur)
	{
		*lst = cur->next;
		ft_lstdelone(cur, del);
		cur = *lst;
	}
}

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	if (!new)
		return ;
	new->next = *alst;
	*alst = new;
}

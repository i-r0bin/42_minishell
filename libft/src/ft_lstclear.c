/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 21:10:17 by rilliano          #+#    #+#             */
/*   Updated: 2023/02/02 21:25:30 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*t;
	t_list	*sw;

	if (!lst || !del)
		return ;
	t = *lst;
	while (t)
	{
		sw = t->next;
		ft_lstdelone(t, del);
		t = sw;
	}
	*lst = NULL;
}

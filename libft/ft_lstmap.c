/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegoube <clegoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 18:25:30 by clegoube          #+#    #+#             */
/*   Updated: 2016/11/14 09:51:13 by clegoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new;
	t_list *tmp;

	new = NULL;
	if (lst && (*f))
	{
		new = (*f)(lst);
		tmp = new;
		while (lst->next)
		{
			tmp->next = (*f)(lst->next);
			if (!tmp)
				return (NULL);
			lst = lst->next;
			tmp = tmp->next;
		}
	}
	return (new);
}

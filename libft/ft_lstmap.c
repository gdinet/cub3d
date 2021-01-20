/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdinet <gdinet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 12:14:47 by gdinet            #+#    #+#             */
/*   Updated: 2019/10/14 14:24:20 by gdinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *))
{
	t_list	*new;
	t_list	*tmp;
	t_list	*elem;

	tmp = lst;
	new = NULL;
	while (tmp)
	{
		if (!(elem = ft_lstnew(f(tmp->content))))
			return (NULL);
		ft_lstadd_back(&new, elem);
		tmp = tmp->next;
	}
	return (new);
}

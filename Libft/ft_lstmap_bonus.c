/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 20:40:52 by ajabri            #+#    #+#             */
/*   Updated: 2023/11/18 21:21:18 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*ret_list;
	void	*data;

	ret_list = NULL;
	if (lst && f && del)
	{
		while (lst)
		{
			data = f(lst->content);
			new_list = ft_lstnew(data);
			if (!new_list)
			{
				del(data);
				ft_lstclear(&ret_list, del);
				return (ret_list);
			}
			ft_lstadd_back(&ret_list, new_list);
			lst = lst->next;
		}
	}
	return (ret_list);
}

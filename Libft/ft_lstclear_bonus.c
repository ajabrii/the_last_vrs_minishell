/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 12:18:42 by ajabri            #+#    #+#             */
/*   Updated: 2023/11/18 21:22:48 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*swp;

	if (!del || !lst || !*lst)
		return ;
	while (*lst)
	{
		swp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = swp;
	}
}

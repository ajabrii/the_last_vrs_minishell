/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbedge.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:50:38 by kali              #+#    #+#             */
/*   Updated: 2024/06/25 16:37:55 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"



t_leak	*ft_leaks_lstlast(t_leak *lst)
{
	t_leak	*tmp;

	if (!lst)
		return (0);
	tmp = lst;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	return (tmp);
}
t_leak	*ft_lstlastv2(t_leak *lst)
{
	t_leak	*tmp;

	if (!lst)
		return (0);
	tmp = lst;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	return (tmp);
}


void	ft_leaks_lstadd_back(t_leak **lst, t_leak *newx)
{
	t_leak	*node;

	if (!lst || !newx)
		return ;
	node = ft_lstlastv2(*lst);
	if (*lst)
		node->next = newx;
	else
		*lst = newx;
}

t_leak	*ft_leaks_lstnew(void *var)
{
	t_leak	*lst;

	lst = (t_leak *)malloc(sizeof(t_leak));
	if (!lst)
		return (NULL);
	lst->address = var;
	lst->next = NULL;
	return (lst);
}

void	*ft_malloc(size_t size)
{
	void	*res;

	res = malloc(size + 1);
	if(!res)
		return (NULL);
	ft_leaks_lstadd_back(&neobash.leaks, ft_leaks_lstnew(res));
	return (res);
}

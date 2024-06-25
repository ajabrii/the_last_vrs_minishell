/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 22:41:42 by ajabri            #+#    #+#             */
/*   Updated: 2023/11/16 12:08:56 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*s;
	char	*dest;

	i = 0;
	dest = (char *)dst;
	s = (char *)src;
	if ((s == NULL && dst == NULL) || n == 0)
		return (dst);
	if (dest > s)
	{
		while (n--)
		{
			dest[n] = s[n];
		}
	}
	else
	{
		while (i < n)
		{
			dest[i] = s[i];
			i++;
		}
	}
	return (dst);
}

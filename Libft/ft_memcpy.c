/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 21:49:11 by ajabri            #+#    #+#             */
/*   Updated: 2023/11/16 12:02:30 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*dest;

	i = 0;
	dest = (unsigned char *)dst;
	s = (unsigned char *)src;
	if ((dst == NULL && src == NULL) || n == 0)
	{
		return (dst);
	}
	while (i < n)
	{
		dest[i] = s[i];
		i++;
	}
	return (dst);
}

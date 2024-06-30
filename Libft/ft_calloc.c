/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 11:42:50 by ajabri            #+#    #+#             */
/*   Updated: 2024/06/25 16:34:06 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	t_size;

	if ((count != 0 && SIZE_MAX / count < size) || (size != 0 && SIZE_MAX
			/ size < count))
		return (NULL);
	t_size = count * size;
	ptr = malloc(t_size);
	if (ptr == NULL)
	{
		return (NULL);
	}
	ft_bzero(ptr, t_size);
	return (ptr);
}

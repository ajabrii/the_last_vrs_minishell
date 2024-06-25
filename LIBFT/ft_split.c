/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:33:23 by ajabri            #+#    #+#             */
/*   Updated: 2023/11/18 11:47:18 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_words(const char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static void	malloc_error_free(char **ret, size_t i)
{
	size_t	j;

	j = 0;
	while (j < i)
	{
		free(ret[j]);
		j++;
	}
	free(ret);
}

static int	ft_mini_malloc(char **ptr, const char *s, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c && ++len)
				s++;
			ptr[i] = ft_substr(s - len, 0, len);
			if (!ptr[i])
			{
				malloc_error_free(ptr, i);
				return (0);
			}
			i++;
		}
		else
			s++;
	}
	ptr[i] = NULL;
	return (1);
}

char	**ft_split(const char *s, char c)
{
	char	**dp;

	if (!s)
		return (NULL);
	dp = malloc(sizeof(char *) * (ft_words(s, c) + 1));
	if (!dp)
		return (NULL);
	if (!ft_mini_malloc(dp, s, c))
		return (NULL);
	return (dp);
}

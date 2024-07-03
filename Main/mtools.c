/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtools.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 06:25:47 by ajabri            #+#    #+#             */
/*   Updated: 2024/07/03 06:29:54 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

char	**grep_paths(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			return (ft_split(env[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

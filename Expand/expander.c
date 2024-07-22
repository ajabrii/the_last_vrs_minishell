/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 06:19:27 by ajabri            #+#    #+#             */
/*   Updated: 2024/07/22 11:20:28 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

char	*ft_expand(char *str)
{
	char *res;
	int	i = 0;

	if (!str)
		return (NULL);
	res = ft_strdup("");
	while (str[i])
	{
		// printf("here\n");
		if (str[i] == '\'')
			res = ft_strjoin(res, handle_squotes(str, &i));
		else if (str[i] == '"' || str[i] == '`')
			res = ft_strjoin(res, handle_dquotes(str, &i));
		else if (str[i] == '$')
			res = ft_strjoin(res, handle_dollar(str, &i));
		else
			res = ft_strjoin(res, normal_str(str, &i));
	}
	return (res);
}

//i have to put last char** that was executed to update that ('_') var.
//when i write that cmd on my shell -> $_ so i have to execute last cmd.
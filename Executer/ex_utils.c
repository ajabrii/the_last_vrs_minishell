/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 10:22:54 by kali              #+#    #+#             */
/*   Updated: 2024/07/22 12:14:08 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

char	*get_cmd_path(char **paths, char *cmd)
{
    // printf("`%s'\n", cmd);
    if (!cmd)
        return (NULL);
    if (cmd[0] == '.')
    {
		if (access(cmd, X_OK) == 0)
			return (cmd);
	}
	if (cmd[0] == '/')
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
	}
	if (!paths)
		return (NULL);
	while (*paths)
	{
		neobash.tmp = ft_strjoin(*paths, "/");
		neobash.palestine = ft_strjoin(neobash.tmp, cmd);
		free(neobash.tmp);
		if (access(neobash.palestine, X_OK) == 0)
			return (neobash.palestine);
		free(neobash.palestine);
		paths++;
	}
	return (NULL);
}

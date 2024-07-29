/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 10:22:54 by kali              #+#    #+#             */
/*   Updated: 2024/07/29 15:23:14 by kali             ###   ########.fr       */
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

int ft_count_size()
{
	int i;

	i = 0;
	while (neobash.envp[i])
		i++;
	return (i);
}

char **get_my_envp()
{
	int i;
	char **res;
	t_env *tmpl;
	int lsize;

	lsize = ft_count_size(neobash.envp) + 1; // change the count_size withe the list_size !!!
	res = ft_malloc(sizeof(char *) * lsize);
	i = 0;
	tmpl = neobash.envl;
	while (tmpl)
	{
		res[i] = ft_strjoinc(tmpl->key, tmpl->value, '=');
		i++;
		tmpl = tmpl->next;
	}
	res[i] = NULL;
	return (res);
}
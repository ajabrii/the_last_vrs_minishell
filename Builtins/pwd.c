/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: venom <venom@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:31:18 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/07/17 11:12:40 by venom            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

t_env *search_envl(char *s)
{
    t_env *env = neobash.envl;
    t_env *tmp = env;

    while (tmp)
    {
        if (!ft_strncmp(s, tmp->key, ft_strlen(s)))
            return (tmp);
        tmp = tmp->next;
    }
    tmp = env;
    return (NULL);
}

//to check option like pwd -h -> error

int option(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '-')
        {
            i++;
            // printf("bash: pwd: '%s': invalid option", str[i]);
            return (1);
        }
        i++;
    }
    if (i > 3)
        return (1);
    return (0);
}

void ft_pwd(char *s)
{
    if (option(s))
        return;
    char *path;
    path = get_env_val("PWD");
    // printf ("str is ::%s\n", s);
    // printf("v->value is ::%s\n", path);
    if (path)
        ft_putstr_fd(path, 1);
    if (path == NULL)
    {
	    path = getcwd(path, 0);
	    if (!path)
		    return;
	    ft_putstr_fd(path, 1);
    }
	ft_putstr_fd("\n", 1);
}

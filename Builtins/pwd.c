/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:31:18 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/07/13 13:50:28 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

t_env *search_env(char *s)
{
    t_env *env = neobash.envl;
    t_env *tmp = env;

    while (tmp)
    {
        if (!ft_strncmp(s, tmp->key, ft_strlen(s)))
            return (tmp->value);
        tmp->next;
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
        if (str[i] == '-'){
            i++;
            printf("bash: pwd: '%s': invalid option", str[i]);
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
    option(s);
    t_env *v = search_env(s);
    if (v->value)
        ft_putstr_fd(v->value, 1);
    if (v == NULL)
    {
	    v->value = getcwd(v->value, 0);
	    if (!v->value)
		    return;
	    ft_putstr_fd(v->value, 1);
    }
	ft_putstr_fd("\n", 1);
}

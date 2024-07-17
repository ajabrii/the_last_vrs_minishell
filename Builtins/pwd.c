/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:31:18 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/07/17 10:12:22 by ajabri           ###   ########.fr       */
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
    option(s);
    t_env *v = search_envl(s);// khassek t fikssi hna pwd makhdamach
    if (!v)
        return;
    printf("segfault v->value [`%p']\n", v);
    if (v->value)
    {
        printf("segfault\n");
        ft_putstr_fd(v->value, 1);
    }
    if (v == NULL)
    {
	    v->value = getcwd(v->value, 0);
	    if (!v->value)
		    return;
	    ft_putstr_fd(v->value, 1);
    }
        // printf("hello\n");
	ft_putstr_fd("\n", 1);
}

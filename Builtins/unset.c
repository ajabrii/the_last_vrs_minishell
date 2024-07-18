/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: venom <venom@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 12:35:31 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/07/17 11:42:58 by venom            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

/*
lets say for exmple i have as a prompt 'unset PATH'
i need to split the prompt by \n to get the the variable name that
i should unset and basecly use the delone function to remove the node
*/

//TO DO

void del(void *full)
{
    free(full);
}

void ft_delone(t_env *lst, void (*del)(void*))
{
    if (!lst || !del)
        return;
    del(lst->key);
    del(lst->value);
    free(lst);
}

void ft_unset(char *s)
{
    // g_shell *neobash;
    t_env *envl = neobash.envl;
    t_env *tmp = envl;
    t_env *prev = NULL;

    // skip spaces here;
    if (!ft_strncmp(s, "unset", 5))
    {
        s += 5;
        while (*(s) == ' ' && *(s))
            s++;
        printf ("str is ::%s\n", s);
        while (tmp)
        {
            if (!ft_strncmp(s, tmp->key, ft_strlen(s)))
            {
                if (prev)
                    prev->next = tmp->next;
                else
                    neobash.envl = tmp->next;
                ft_delone(tmp, del);
                return;
            }
            else
            {
                prev = tmp;
                tmp = tmp->next;
            }
        }
        	ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(s, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
    }
}


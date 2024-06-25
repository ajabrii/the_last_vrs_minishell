/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:57:56 by kali              #+#    #+#             */
/*   Updated: 2024/06/25 16:10:18 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"


size_t ft_strlenc(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

t_env	*ft_env_lstnew(char *var)
{
	t_env	*lst;
	int		len;

	lst = (t_env*)malloc(sizeof(t_env));
	if (!lst)
		return (NULL);
	lst->key = ft_malloc(ft_strlenc(var, '='));
	ft_strcpy(lst->key, var, '=');
	len = ft_strlen(lst->key);
	lst->value = ft_malloc(ft_strlenc((var + len), '\0'));
	ft_strcpy(lst->value, var + len + 1, '\0');
	lst->next = NULL;
	return (lst);
}

t_env	*ft_env_lstlast(t_env *lst)
{
	t_env	*tmp;

	if (!lst)
		return (0);
	tmp = lst;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	return (tmp);
}

void ft_env_lstadd_back(t_env **lst, t_env *newx)
{
	t_env	*node;

	if (!lst || !newx)
		return ;
	node = ft_env_lstlast(*lst);
	if (*lst)
		node->next = newx;
	else
		*lst = newx;
}



void    get_env_list(char **env)
{
    int i;
    if (!env)
        return ;
    i = 0;
    while (env[i])
    {
        ft_env_lstadd_back(&neobash.envl, ft_envlstnew(env[i]));
        i++;
    }
    // shell.size = i;
    // ft_env();
}

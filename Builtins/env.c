/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: venom <venom@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 12:36:18 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/07/17 10:59:51 by venom            ###   ########.fr       */
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

void    ft_strcpy(char *dst, char *src, char c)
{
    int i;

    i = 0;
    while (src[i] && src[i] != c)
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
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

t_env	*ft_envlst_new(char *key, char *value)
{
	t_env	*new;

	new = (t_env*)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
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
        ft_env_lstadd_back(&neobash.envl, ft_env_lstnew(env[i]));
        i++;
    }
    // shell.size = i;
    // ft_env(neobash.envl);
}

void    ft_env(t_env *env)
{
    t_env *tmp;

    tmp = env;
    while (tmp)
    {
        printf("%s=%s\n",tmp->key, tmp->value);
        tmp = tmp->next;
    }
	printf("END HERE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
}

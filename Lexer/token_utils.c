/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:44:23 by kali              #+#    #+#             */
/*   Updated: 2024/06/25 16:31:53 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"


bool ft_is_quote(char c)
{
    if (c == 39 || c == 34)
        return (true);
    else
        return (false);
}

void    ft_skips(char **line)
{
    if (**line && ft_isspace(**line))
        (*line)++;
}


bool ft_is_separator(char *line)
{
    if (!ft_strncmp(line, "(", 1) || !ft_strncmp(line, ">", 1)
			|| !ft_strncmp(line, "|", 1) || !ft_strncmp(line, "&&", 2)
			|| !ft_strncmp(line, "<", 1) || !ft_strncmp(line, ")", 1))
        return (true);
    else
        return (false);
}

t_token *ft_tokennew(t_token_t type, char *v)
{
    t_token *res;

    res = ft_malloc(sizeof(t_token));
    res->value = v;
    res->type = type;
    res->next = NULL;
    return (res);
}

void ft_token_addback(t_token **head, t_token *ntoken)
{
    t_token *tmp;

    if (!*head)
    {
        *head = ntoken;
        return ;
    }
    tmp = *head;
    while (tmp && tmp->next)
        tmp = tmp->next;
    tmp->next = ntoken;
}

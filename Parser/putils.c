/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:53:42 by kali              #+#    #+#             */
/*   Updated: 2024/06/30 13:45:29 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

char *ft_strjoinc(const char *s1, const char *s2, char c)
{
    char	*res;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
    if ((!c || !ft_strlen(s1) || !ft_strlen(s2)))
    {
        return (ft_strjoin(s1, s2));
    }
	res = ft_malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i++] = c;
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}
t_io *create_io_node(char *val, t_io_t type)
{
    t_io *res;

    res = ft_malloc(sizeof(t_io));
    res->value = ft_strdup(val);
    res->type = type;
    res->next = NULL;
    return (res);
}

t_io_t get_type(t_token_t tk)
{
    if (tk == APPEND)
        return (APP);
    else if (tk == HEREDOC)
        return (HERE_DOC);
    else if (tk == INPUT)
        return (IN);
    // else if (tk == REDIRECT)
    //     return (OUT);
    return (OUT);
}

void ft_addback_io_node(t_io **iop, t_io *new)
{
    t_io *tmp;

    if (!*iop)
    {
        *iop = new;
        return;
    }
    tmp = *iop;
    while (tmp && tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}
bool    create_iol(t_io **io, t_io_t io_t)
{
    t_io *new;

    if (neobash.prs_state)
        return (false);
    while (neobash.cur_tok && is_io())
    {
        ft_skip_tok();
        if (!neobash.cur_tok || neobash.cur_tok->type != WRD)
            return (set_state(1), false);
        new = create_io_node(neobash.cur_tok->value, io_t);
        if (!new)
            return (set_state(2), false);
        ft_addback_io_node(io, new);
        ft_skip_tok();
    }
    return (true);
}
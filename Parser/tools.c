/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:23:57 by kali              #+#    #+#             */
/*   Updated: 2024/06/26 09:18:56 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

void set_state(int state)
{
    // 0 no problem
    // 1 is a syntax problem
    // 2 other errors and problems
    neobash.prs_state = state;
}
void ft_skip_tok()
{
    neobash.cur_tok = neobash.cur_tok->next;
}

bool is_pair()
{
    if (!neobash.cur_tok)
        return (false);
    if (neobash.cur_tok->type == OR || neobash.cur_tok->type == AND || neobash.cur_tok->type == PIPE)
        return (true);
    else
        return (false);
}

bool is_io()
{
    if (neobash.cur_tok->type == APPEND || neobash.cur_tok->type == REDIRECT
            || neobash.cur_tok->type == INPUT || neobash.cur_tok->type == HEREDOC)
        return (true);
    else
        return (false);
}

t_node *ft_newnode(t_root_t node_t)
{
    t_node *res;

    res = ft_malloc(sizeof(t_node));
    res->type = node_t;
    res->args = NULL;
    res->left = NULL;
    res->right = NULL;
    res->iol = NULL;
    return (res);
}
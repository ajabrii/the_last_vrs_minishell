/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:58:34 by kali              #+#    #+#             */
/*   Updated: 2024/07/17 10:57:30 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

bool ft_argv(char **cmd)
{
    char *tmp;

    if (neobash.prs_state)
        return (NULL);
    if (!*cmd)
        *cmd = ft_strdup("");
    if (!*cmd)
        return (NULL);
    while (neobash.cur_tok && neobash.cur_tok->type == WRD)
    {
        tmp = *cmd;
        *cmd = ft_strjoinc(*cmd, neobash.cur_tok->value, ' ');
        if (!*cmd)
            return (set_state(2), false);
        free(tmp);
        ft_skip_tok();
    }
    return (true);
}


t_node *ft_scmd()
{
    t_node *result;

    if (neobash.prs_state)
        return (NULL);
    result = ft_newnode(CMD_N);
    if (!result)
        return (set_state(2), NULL);
    // result->args = NULL;
    while (neobash.cur_tok && (neobash.cur_tok->type == WRD || is_io()))
    {
        if (neobash.cur_tok->type == WRD)
        {
            if (!ft_argv(&result->args))
                return (set_state(2),NULL);
        }
        else if (is_io())
        {
            // printf("IO\n");
            // printf(RED"[[[  %d ]]][`%s']\n"RES, neobash.cur_tok->type, neobash.cur_tok->value);
            if (!create_iol(&result->iol, get_type(neobash.cur_tok->type)))
                return (free(result->args), free(result), NULL);
        }
    }
    return (result);
}

t_node *ft_left_hand()
{
    t_node *result;
    t_node *tmp;

    if (neobash.prs_state || !neobash.cur_tok)
        return (NULL);
    if (neobash.cur_tok->type == R_PARENT || is_pair())
        return (set_state(1), NULL);
    else if (neobash.cur_tok->type == L_PARENT)
    {
        neobash.flag = 1;
        ft_skip_tok();
        result = ft_rdp(0);
        if (!result)
            return (set_state(2), NULL);
        if (!neobash.cur_tok || neobash.cur_tok->type != R_PARENT)
            return (set_state(1), NULL);
        ft_skip_tok();
        // printf(RED "[%s]-[%d]\n" RES, neobash.cur_tok->value, neobash.cur_tok->type);
        if (neobash.cur_tok && !is_pair())
        {
            tmp = ft_rdp(5);
            result->iol = tmp->iol;
        }
        return (result);
    }
    else
        return (ft_scmd());
}

int ft_precedence(t_token_t tp)
{
    if (tp == PIPE)
        return 2;
    else if (tp == OR)
        return 1;
    else if (tp == AND)
        return 0;
    else
        return -1;
}


t_root_t get_node_t(t_token_t tk)
{
    if (tk == PIPE)
        return (PIPE_N);
    else if (tk == AND)
        return (AND_N);
    else if (tk == OR)
        return (OR_N);
    return (NOTHING);
}
t_node *create_pair_node(t_node *left, t_node *right, t_root_t node_t)
{
    t_node *root;

    root = ft_newnode(node_t);
    root->left = left;
    root->right = right;
    return (root);
}

t_node *ft_rdp(int p)
{
    t_node *left;
    t_node *right;
    t_token_t tmp;

    if (neobash.prs_state)
        return (NULL);
    left = ft_left_hand();
    if (!left)
        return (NULL);
    while (is_pair() && ft_precedence(neobash.cur_tok->type) >= p)
    {
        tmp = neobash.cur_tok->type;
        ft_skip_tok();
        if (!neobash.cur_tok)
            return (set_state(1), left);
        neobash.np = ft_precedence(tmp) + 1;
        right = ft_rdp(neobash.np);
        if (!right)
            return (left);
        left = create_pair_node(left, right, get_node_t(tmp));
        if (!left)
            return (NULL); // free here;
    }
    return (left);
}

t_node  *ft_parser()
{
    t_node      *tree_root;

    neobash.cur_tok = neobash.tokens;
    tree_root = ft_rdp(0);
    if (neobash.cur_tok)
        return (set_state(1), tree_root);
    return (tree_root);
}
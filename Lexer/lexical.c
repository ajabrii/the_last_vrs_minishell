/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 19:01:04 by kali              #+#    #+#             */
/*   Updated: 2024/06/25 19:13:21 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"


// create separator node
// bool ft_add_sp_node(char **line, t_token **tokens, t_token_t type)
// {
//     if (!ft_token_addback(tokens, ft_tokennew(type, NULL)))
//         return (false);
//     *line++;
//     if (type == APPEND || type == OR || type == AND || type == HEREDOC)
//         *line++;
//     return (true);
// }

int ft_token_sp(t_token **tokens, char **line)
{
    if (!ft_strncmp(*line, ">>", 2))
        return(ft_add_sp_node(line, tokens, APPEND) && 1);
    else if (!ft_strncmp(*line, "<<", 2))
        return(ft_add_sp_node(line, tokens, HEREDOC) && 1);
    else if (!ft_strncmp(*line, "<", 1))
        return(ft_add_sp_node(line, tokens, INPUT) && 1);
    else if (!ft_strncmp(*line, ">", 1))
        return(ft_add_sp_node(line, tokens, REDIRECT) && 1);
    else if (!ft_strncmp(*line, "&&", 2))
        return(ft_add_sp_node(line, tokens, AND) && 1);
    else if (!ft_strncmp(*line, "||", 2))
        return(ft_add_sp_node(line, tokens, OR) && 1);
    else if (!ft_strncmp(*line, "(", 1))
        return(ft_add_sp_node(line, tokens, L_PARENT) && 1);
    else if (!ft_strncmp(*line, ")", 1))
        return(ft_add_sp_node(line, tokens, R_PARENT) && 1);
    else
        return(ft_add_sp_node(line, tokens, PIPE) && 1);
}
int	ft_is_separatorv2(char *s)
{
	if (!ft_strncmp(s, "&&", 2) || *s == ' ' || *s == '\t'
		|| *s == '<' || *s == '>' || *s == '|' || *s == '(' || *s == ')')
		return (1);
	return (0);
}

int    ft_add_identifier(t_token **tokens, char **line)
{
    char    *v;
    int     i;
    char    *ptr;
    t_token *new;

    ptr = *line;
    i = 0;
    while (ptr[i] && (!ft_is_separatorv2(ptr + i)))
    {
        if (ft_is_quote(ptr[i]))
        {
            if (!ft_skipq(ptr, &i)) // skip the quotes
            {
                return (0); // To Do quotes error
            }
        }
        else
            i++;
    }
    v = ft_substr(ptr, 0, i); // i need to change all malloc into ft_malloc
    // printf("[v'%s'][ptr'%s'][start'%c'][end'%c']\n", v, ptr, ptr[0], ptr[i - 1]);
    if (!v)
        return (0);
    new = ft_tokennew(WRD, v);
    if (!new)
        return (free(v), 0);
    *line += i;
    return (ft_token_addback(tokens, new), 1); // probably somthing wrong here so when i start debuging take this in 3ayn al i3tibar
}

t_token *ft_tokenizer(char *line)
{
    t_token *token_h; // token head;
    int flag;

    flag = 0;
    token_h = NULL;
    while (*line)
    {
        if (flag)
            return (NULL); // free here
        if (ft_isspace(*line))
            ft_skips(&line);
        else if (!ft_strncmp(line, "<", 1) || !ft_strncmp(line, ">", 1)
			|| !ft_strncmp(line, "|", 1) || !ft_strncmp(line, "&&", 2)
			|| !ft_strncmp(line, "(", 1) || !ft_strncmp(line, ")", 1))
        {
            // printf("hello separator\n");
            flag = (!ft_token_sp(&token_h, &line));
        }
        else
        {
            // printf("hello identifier\n");
            flag = (!ft_add_identifier(&token_h, &line) && 1);
        }
    }
    return (token_h);
}

t_token *ft_lexer()
{
    t_token *token_l;

    token_l = ft_tokenizer(neobash.line);
    free(neobash.line);
    neobash.line = NULL;
    t_token *n = token_l;
    while (n)
    {
        printf("value:[%s]_____type[%d]\n",n->value, n->type);
        n = n->next;
    }
    // exit(126);
    return (token_l);
}
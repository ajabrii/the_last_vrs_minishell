/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:16:25 by ajabri            #+#    #+#             */
/*   Updated: 2024/07/01 10:06:14 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

void ft_err(char *err,int flag)
{
    write(2, err, ft_strlen(err));
    write(2, "\n", 1);
    if (!flag)
        exit(1);
}
void ft_coutquotes()
{
	int i;

	i = 0;
	int dq = 0;
	int sq = 0;
	while (neobash.line[i])
	{
		if (neobash.line[i] == 34)
			dq += 1;
		else if(neobash.line[i] == 39)
			sq += 1;
		i++;
	}
	if (sq % 2 != 0)
        ft_err("neoneobash: the single qoutes are not closed", 1);
    if (dq % 2 != 0)
        ft_err("neoneobash: the double qoutes are not closed", 1);

}

void    give_token()
{
    t_token *head;
    int i;

    // int sub_count = ft_countv2(neobash.sub);
    i = 0;
    head = NULL;
    while (neobash.sub[i])
    {
        if (is_whitespaces(*neobash.sub[i]))
            i++;
        if (!neobash.sub[i])
            break;
        ft_lstadd_backv3(&head, ft_lstnewv3(neobash.sub[i], set_token(i)));
        // printf("`%s'\n", neobash.sub[i]);
        i++;
    }
    neobash.tokens = head;
//     // expander();
    // while (head)
    // {
    //     // printf("node[%s][%d]\n", head->value, head->token);
    //     printf("[%s]-[%d]\n", head->value, head->type);

    //     head = head->next;
    // }
}

void ft_lexer()
{
    ft_lexical();
    give_token();
}

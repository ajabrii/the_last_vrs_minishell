/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:20:20 by ajabri            #+#    #+#             */
/*   Updated: 2024/06/30 06:25:51 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

void ft_lexical()
{
    int i;

    i = 0;
    int start = 0;
    int ntoken = 0;
    int len;

    ft_coutquotes();
    neobash.sub = ft_malloc(sizeof(char *) * (ft_strlen(neobash.line) + 1));
    while (neobash.line[i])
    {

        if (is_quotition(neobash.line[i]))
        {
            start = i;
            len = count_inside_quotes(i, neobash.line[i]);
            neobash.sub[ntoken] = ft_substr(neobash.line, start, len - start);
            ntoken++;
            i = len;
        }
        else if (check_spcial(neobash.line[i]))
        {
            if (is_whitespaces(neobash.line[i]))
            {
                len = count_whitespaces(neobash.line, i);
                neobash.sub[ntoken] = ft_substr(neobash.line, i, len);
                i += len;
            }
            else if (check_red_or_and(neobash.line, i))
            {
                neobash.sub[ntoken] = ft_substr(neobash.line, i, 2);
                i += 2;
            }
            else
            {
                neobash.sub[ntoken] = ft_substr(neobash.line, i, 1);
                i++;
            }
            ntoken++;
        }
        else
        {
            start = i;
            while (!check_spcial(neobash.line[i]))
                i++;
            neobash.sub[ntoken] = ft_substr(neobash.line, start, i - start);
            ntoken++;
        }
    }
    neobash.sub[ntoken] = NULL;
}


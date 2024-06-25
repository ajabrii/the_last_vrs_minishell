/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:49:00 by kali              #+#    #+#             */
/*   Updated: 2024/06/25 16:32:04 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"


bool    ft_skipq(char *line, int *i)
{
    char	quote;

	quote = line[*i];
	if (ft_strchr(line + *i + 1, quote))
	{
		(*i)++;
		while (line[*i] != quote)
			(*i)++;
		(*i)++;
		return (true);
	}
	return (false);
}


int ft_add_sp_node(char **line, t_token **tokens, t_token_t type)
{
	t_token *tok;
	tok = ft_tokennew(type, NULL);
	if (!tok)
		return (0);
	ft_token_addback(tokens, tok);
	(*line)++;
	if (type == APPEND || type == OR || type == AND || type == HEREDOC)
        (*line)++;
    return (1);
}

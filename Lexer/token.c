/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 10:16:34 by ajabri            #+#    #+#             */
/*   Updated: 2024/07/01 10:01:10 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

    i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
    {
        i++;
    }
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

bool is_quotition(char i)
{
    if (i == 34)
        return (true);
    if (i == 39)
        return (true);
    else
        return (false);
}


int count_inside_quotes(int i, char q)
{
    i++;
    while (neobash.line[i] && neobash.line[i] != q)
    {
        i++;
    }
    if (neobash.line[i] == q)
        i++;
    return i; // Return the index of the ending quote character
}

int count_whitespaces(char *line, int i)
{
    int count;

    count = 0;
    while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\v'))
    {
        i++;
        count += 1;
    }
    return (count);
}

bool is_whitespaces(char line)
{
    if (line == ' ' || line == '\t' || line == '\v')
        return (true);
    return (false);
}
bool is_badchar(char *c)
{
    if (c[0] == ';' || c[0] == '`' || c[0] == '\\' || c[0] == '{' || c[0] == '}')
        return (true);
    if (c[0] == '[' || c[0] == ']' || c[0] == '@' || c[0] == '#' || c[0] == '%')
        return (true);
    if (c[0] == '!' || c[0] == ':')
        return (true);
    if (c[0] == '&' && ft_strlen(c) == 1)
        return (true);
    else
        return (false);
}
t_token_t set_token(int i)
{
    if (!ft_strncmp(neobash.sub[i], ">",1))
        return (REDIRECT);
    else if (!ft_strncmp(neobash.sub[i], "<", 1))
        return (INPUT);
    else if (!ft_strncmp(neobash.sub[i], ">>", 2))
        return (APPEND);
    else if (!ft_strncmp(neobash.sub[i], "<<", 2))
        return (HEREDOC);
    // else if (!ft_strncmp(neobash.sub[i], "*", ft_strlen(neobash.sub[i])))
    //     return (STAR);
    else if (!ft_strncmp(neobash.sub[i], "&&", 2))
        return (AND);
    else if (!ft_strncmp(neobash.sub[i], "||", 2))
        return (OR);
    else if (!ft_strncmp(neobash.sub[i], "|", 1))
        return (PIPE);
    else if (!ft_strncmp(neobash.sub[i], "(", 1))
        return (L_PARENT);
    else if (!ft_strncmp(neobash.sub[i], ")", 1))
        return (R_PARENT);
    else if (is_badchar(neobash.sub[i]))
        return (SYNTAX);
    else
    {
        return (WRD);
    }
}

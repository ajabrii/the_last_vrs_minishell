/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 12:36:11 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/07/06 18:00:39 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	if (n == 0)
// 		return (0);
// 	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
// 	{
// 		i++;
// 	}
// 	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// }

int param(char *s)
{
    int i = 4;
    while (s[i] && s[i] == ' ')
        i++;
    if (s[i] == '-')
        i++;
    if(!s[i])
        return (0);
    while (s[i] && s[i] == 'n')
        i++;
    while (s[i] && (s[i] == ' '))
        i++;
    return (i);
}


void ft_echo(char *s)
{
    bool nl = false;
    bool sq = false;
    bool dq = false;
    int count = 0;
    int i = 0;

    i = param(s);
    if (i == 0)
        return;
    while (s[i])
    {
        if (s[i] == '\"' && !sq)
            dq = !dq;
        else if (s[i] == '\'' && !dq)
            sq = !sq;
        else
            printf("%c", s[i]);
        i++;
    }
    if (!nl)
        printf("\n");
}

// int main()
// {
//     ft_echo("echo  \'b\'\"o\"nj\"o\"\'u\'r");
// }
// int skip_spaces(char *str)
// {
//     int i = 0;
//     while (str[i] && (str[i] == ' '))
//         i++;
//     if (!str[i])
//         return (0);
//     return (i);
// }
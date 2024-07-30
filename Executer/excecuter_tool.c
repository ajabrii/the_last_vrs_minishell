/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excecuter_tool.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:05:40 by kali              #+#    #+#             */
/*   Updated: 2024/07/30 15:39:38 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"
# include <ctype.h>


static size_t	ft_wordsv(const char *s)
{
	size_t	i;
	size_t	count;
	bool	in_quotes;

	i = 0;
	count = 0;
	in_quotes = false;
	while (s[i] != '\0')
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			in_quotes = !in_quotes;
			i++;
		}
		else if (isspace(s[i]) && !in_quotes)
			i++;
		else
		{
			count++;
			while (s[i] && (!isspace(s[i]) || in_quotes))
			{
				if (s[i] == '"' || s[i] == '\'')
					in_quotes = !in_quotes;
				i++;
			}
		}
	}
	return (count);
}

static void	malloc_error_free(char **ret, size_t i)
{
	size_t	j;

	j = 0;
	while (j < i)
	{
		free(ret[j]);
		j++;
	}
	free(ret);
}

static int	ft_mini_mallocv(char **ptr, const char *s)
{
	size_t	i;
	size_t	len;
	bool	in_quotes;

	i = 0;
	in_quotes = false;
	while (*s)
	{
		if (isspace(*s) && !in_quotes)
			s++;
		else
		{
			len = 0;
			while (*s && (!isspace(*s) || in_quotes))
			{
				if (*s == '"' || *s == '\'')
					in_quotes = !in_quotes;
				len++;
				s++;
			}
			ptr[i] = ft_substr(s - len, 0, len);
			if (!ptr[i])
			{
				malloc_error_free(ptr, i);
				return (0);
			}
			i++;
		}
	}
	ptr[i] = NULL;
	return (1);
}

char	**ft_splitv2(const char *s)
{
	char	**dp;

	if (!s)
		return (NULL);
	dp = malloc(sizeof(char *) * (ft_wordsv(s) + 1));
	if (!dp)
		return (NULL);
	if (!ft_mini_mallocv(dp, s))
		return (NULL);
	return (dp);
}



char *ft_quotes_trimer(char *str)
{
    if (!str)
        return NULL;

    // int i = 0;
    int start = 0;
    int end = strlen(str) - 1;

    // Check if the string starts and ends with the same quote character
    if ((str[start] == '\"' && str[end] == '\"') || (str[start] == '\'' && str[end] == '\''))
    {
        // Move start and end to skip the quotes
        start++;
        end--;
    }

    // Calculate the new length for the trimmed string
    int len = end - start + 1;

    // Allocate memory for the new string
    char *res = malloc(len + 1);
    if (!res)
        return NULL;

    // Copy the trimmed portion into the new string
    strncpy(res, str + start, len);
    res[len] = '\0'; // Null-terminate the new string

    return res;
}

// char *ft_quotes_trimer(char *str)
// {
//     if (!str)
//         return(NULL);
//     int i;
//     char q;
//     char *res;
//     int start;

//     i = 0;
//     while (str[i])
//     {
//         if (str[i] == '\"' || str[i] == '\'')
//         {
//             q = str[i];
//             i++;
//             start = i;
//         }



//     }
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 06:20:30 by ajabri            #+#    #+#             */
/*   Updated: 2024/07/18 06:20:31 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

char *normal_str(char *str, int *i)
{
	int start;

	start = *i;
	while (str[*i] && str[*i] != '\'' && str[*i] != '"'
	&& str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

char *handle_squotes(char *str, int *i)
{
	int start = *i;

	(*i)++;
	while (str[*i] != '\'')
		(*i)++;
	(*i)++;
	return (ft_substr(str, start, *i - start));
}

char *handle_dquotes(char *str, int *i)
{
	char *res;

	res = ft_strdup("\"");
	(*i)++;
	while (str[*i] != '\"')
	{
		if (str[*i] == '$')
			res = ft_strjoin(res, handle_dollar(str, i));
		else
			res = ft_strjoin(res, dquote_str(str, i));
	}
	(*i)++;
	return (ft_strjoin(res, "\""));
}

char	*dquote_str(char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] != '"' && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*handle_dollar(char *str, int *i)
{
	int		start;
	char	*var;
	char	*value;

	// printf("here\n");
	(*i)++;
	// if (str[i] == '?')
		// return ();//here i have to put exit status
	if (str[*i] == '$')
	{
		(*i)++;
		return (ft_substr(str, *i - 2, 2));
	}
	if (!valid_char(str[*i]))
	{
		printf("empty\n");
		return (ft_strdup(""));
	}
	start = *i;
	// printf("%i\n", (*i));
	while (valid_char(str[*i]))
		(*i)++;
	var = ft_substr(str, start, *i - start);
	value = get_env_val(var);
	if (!value)
		return (free(var), ft_strdup(""));
	return (free(var), ft_strdup(value));
}

bool	valid_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

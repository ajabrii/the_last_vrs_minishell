/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:12:06 by kali              #+#    #+#             */
/*   Updated: 2024/07/22 11:16:24 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

bool	ft_is_delimiter(char *delimiter, char *str)
{
	while (*str)
	{
		if (*delimiter == '"' || *delimiter == '\'')
		{
			delimiter++;
			continue ;
		}
		else if (*str == *delimiter)
		{
			str++;
			delimiter++;
		}
		else
			return (false);
	}
	while (*delimiter == '"' || *delimiter == '\'')
		delimiter++;
	return (!*delimiter);
}

void	heredoc_f(t_io *io)
{
	char	*line;
	char	*quotes;

	quotes = io->value;
	while (*quotes && *quotes != '"' && *quotes != '\'')
		quotes++;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_is_delimiter(io->value, line))
			break ;
		else
		{
			ft_putstr_fd(line, neobash.fd[1]);
			ft_putstr_fd("\n", neobash.fd[1]);
		}
	}
	// leaks
	// exit(0);
}

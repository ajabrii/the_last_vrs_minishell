/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:24:37 by kali              #+#    #+#             */
/*   Updated: 2024/07/22 11:26:18 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

int	ft_out(t_io *io)
{
	int		fd;
    int     ex;

    ex = 0;
    // if (!io->expanded_value || io->expanded_value[1])
    // {
    // 	ex = ft_err_msg(
    // 			(t_err){ENO_GENERAL, ERRMSG_AMBIGUOUS, io_list->value});
    // 	return (*status);
    // }
    fd = open(io->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    // printf(ORG"{``%d''}\n"RES, fd);
    if (fd == -1)
    {
		printf("neobash: %s: Permission denied\n",io->value);
        ex = 1;
        return (ex);
	}
	dup2(fd, STDOUT_FILENO);
	// close(fd);
	ex = 0;
	return (ex);
}

int	ft_in(t_io *io)
{
	int		fd;
    int     ex;

    ex = 0;
    // if (!io->expanded_value || io->expanded_value[1])
    // {
    // 	ex = ft_err_msg(
    // 			(t_err){ENO_GENERAL, ERRMSG_AMBIGUOUS, io_list->value});
    // 	return (*status);
    // }
    fd = open(io->value, O_RDONLY);
	if (fd == -1)
	{
        printf("neobash: %s: Permission denied\n",io->value);
        ex = 1;
        return (ex);
    }
	dup2(fd, STDIN_FILENO);
	close(fd);
	ex = 0;
	return (ex);
}

int	ft_app(t_io *io)
{
	int		fd;
    int     ex;

    ex = 0;
    // if (!io->expanded_value || io->expanded_value[1])
    // {
    // 	ex = ft_err_msg(
    // 			(t_err){ENO_GENERAL, ERRMSG_AMBIGUOUS, io_list->value});
    // 	return (*status);
    // }
    fd = open(io->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
        // ex = ft_err_msg(ft_check_write(io->value)); msg
        printf("neobash: %s: Permission denied\n",io->value);
        ex = 1;
        return (ex);
    }
	dup2(fd, STDOUT_FILENO);
	close(fd);
	ex = 0;
	return (ex);
}

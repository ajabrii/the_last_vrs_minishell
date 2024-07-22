/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_io.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:21:40 by kali              #+#    #+#             */
/*   Updated: 2024/07/22 11:28:27 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

void ft_init_io(t_node *root)
{
    pid_t pid;
    t_io *io;

    if (!root)
        return;
    root->args = ft_expand(root->args);
    io = root->iol;
    while (io)
    {
        // printf("[%s]-[%d]\n", io->value, io->type);
        if (io->type == HERE_DOC)
        {
            // printf("Hello \n");
            // neobash.hdoc = 0;
            pipe(neobash.fd);
            pid = fork();
            if (!pid)
            {
                heredoc_f(io);
                // exit(0);
            }
            else
            {
                waitpid(pid, NULL, 0);
                close(neobash.fd[1]);
                close(neobash.fd[0]);
            }
        }
        // else
        // {
        //     printf("hello else\n");
        //     // io->exp_val = ft_expand(io->value);
        // }
        io = io->next;
    }
}

int ft_io(t_node *root)
{
    t_io *tmp_io;
    int ex;

    tmp_io = root->iol;
    ex = 0;
    while (tmp_io)
    {
        if (tmp_io->type == OUT)
        {
            ex = ft_out(tmp_io);
            if (ex)
                return (ex);
        }
        else if (tmp_io->type == IN)
        {
            ex = ft_in(tmp_io);
            if (ex)
                return (ex);
        }
        else if (tmp_io->type == APP)
        {
            ex = ft_app(tmp_io);
            if (ex)
                return (ex);
        }
        tmp_io = tmp_io->next;
    }
    return (0);
}
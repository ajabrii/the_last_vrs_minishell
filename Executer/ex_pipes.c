/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:29:05 by kali              #+#    #+#             */
/*   Updated: 2024/07/22 11:29:42 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

void    ex_lpipe(int fd[2], t_node *root)
{
    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);
    neobash.status = ft_executer(root);
    exit(neobash.status);
}

void    ex_rpipe(int fd[2], t_node *root)
{
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
    neobash.status = ft_executer(root);
    exit(neobash.status);
}

int ex_pipes(t_node *root)
{
    int fd[2];
    pid_t pid0;
    pid_t pid1;

    if (pipe(fd))
        return (1);
    pid0 = fork();
    if (pid0 < 0)
        return (1);
    if (!pid0)
        ex_lpipe(fd, root->left);
    else
    {
        pid1 = fork();
        if (pid1 < 0)
            return (1);
        if (!pid1)
            ex_rpipe(fd, root->right);
        else
        {
            close(fd[0]);
            close(fd[1]);
            waitpid(pid0,NULL, 0);
            waitpid(pid1,NULL, 0);
            return (neobash.status);
        }
    }
    return (42);
}

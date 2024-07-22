/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:08:37 by ajabri            #+#    #+#             */
/*   Updated: 2024/07/22 11:29:32 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

void ft_before_exec(t_node *root)
{
    t_root_t tp;

    if (!root)
        return;
    tp = root->type;
    if (tp == PIPE_N || tp == OR_N || tp == AND_N)
    {
        ft_before_exec(root->left);
        // if (neobash.hdoc)
        ft_before_exec(root->right);
    }
    else
        ft_init_io(root);
}

void	ft_reset_stds()
{
	// if (piped)
	// 	return ;
	// printf("{%d}\n",neobash.in);
	dup2(neobash.in, 0);
	dup2(neobash.out, 1);
}

bool is_builtin(t_node *root)
{
    if (!ft_strncmp(root->args,"cd", 2))
        return (true);
    if (!ft_strncmp(root->args,"env", 3))
        return (true);
    if (!ft_strncmp(root->args,"exit", 4))
        return (true);
    if (!ft_strncmp(root->args,"pwd", 3))
        return (true);
    if (!ft_strncmp(root->args,"unset", 5))
        return (true);
    if (!ft_strncmp(root->args,"echo", 4))
        return (true);
    if (!ft_strncmp(root->args,"export", 6))
        return (true);
    if (!ft_strncmp(root->args,"./minishell", 11))
        return (true);
    else
        return (false);
}

int     ex_builtins(t_node *root)
{
    if (!ft_strncmp(root->args,"cd", 2))
    {
        bt_cd(root->args);
        return (0);
    }
    if (!ft_strncmp(root->args,"env", 3))
        return (ft_env(neobash.envl), 0);
    if (!ft_strncmp(root->args,"exit", 4))
    {
        // printf("here [%s]\n", root->args);
        ft_exit(0);
        return (0);
    }
    if (!ft_strncmp(root->args,"pwd", 3))
    {
        // printf("here [%s]\n", root->args);
        ft_pwd(root->args);
        return (0);
    }
    if (!ft_strncmp(root->args,"unset", 5))
        return (ft_unset(root->args), 0);
    if (!ft_strncmp(root->args,"echo", 4))
        return (ft_echo(root->args), 0);
    if (!ft_strncmp(root->args,"export", 6))
        return (ft_export(root->args), 0);
    if (!ft_strncmp(root->args,"./minishell", 11))
        return (update_env("SHLVL", ft_itoa(++neobash.level)), 0);
    else
        return (1);
}

unsigned int ex_cmd(t_node *root)
{
    char **args;
    char *cmdpath;
    pid_t pid;
    // int fd;
    int ex;

    // fd = 0;

    // if (root->iol)
    // {
    //     ex = ft_io(root);
    //     return (ft_reset_stds(), ex);
    // }
    if (root->args)
    {
    // ex = 0;
        // if (!args)
            // printf("segfault\n");
        if (is_builtin(root)) // TO DO
        {
            // printf("here1\n");
            ex = ex_builtins(root); // TO DO
            if (ex)
                exit(ex);
        }
        else
        {
            pid = fork();
            if (!pid)
            {
                args = ft_split(root->args, ' ');
                cmdpath = get_cmd_path(neobash.paths, args[0]);
                ex =ft_io(root);
                if (ex)
                {
                    printf("exit\n");
                    exit(ex);
                }
                else
                {
                    execve(cmdpath, args, neobash.envp);
                    printf("neobash: command not found: %s\n", args[0]);
                    return (127);
                }
            }
            else
            {
                wait(NULL);
                return (0);
            }
        }

    }
    return (0);
}

int ft_executer(t_node *root)
{
    int exit;

    exit = 1337;
    if (root->type == PIPE_N)
        return (ex_pipes(root));
    else if (root->type == AND_N)
    {
        exit = ft_executer(root->left);
        if (exit == 0)
            return (ft_executer(root->right));
        return (exit);
    }
    else if (root->type == OR_N)
    {
        exit = ft_executer(root->left);
        if (exit != 0)
            return (ft_executer(root->right));
        return (exit);
    }
    else
        return (ex_cmd(root));
    return (exit);
}

void execution()
{
    if (!neobash.tree)
        return;
    ft_before_exec(neobash.tree);
    neobash.status = ft_executer(neobash.tree);
}


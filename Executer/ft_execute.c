/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:08:37 by ajabri            #+#    #+#             */
/*   Updated: 2024/07/06 11:25:02 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

char	*get_cmd_path(char **paths, char *cmd)
{
	if (cmd[0] == '.')
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
	}
	if (cmd[0] == '/')
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
	}
	if (!paths)
		return (NULL);
	while (*paths)
	{
		neobash.tmp = ft_strjoin(*paths, "/");
		neobash.palestine = ft_strjoin(neobash.tmp, cmd);
		free(neobash.tmp);
		if (access(neobash.palestine, X_OK) == 0)
			return (neobash.palestine);
		free(neobash.palestine);
		paths++;
	}
	return (NULL);
}


unsigned int ex_cmd(t_node *root)
{
    char **args;
    char *cmdpath;
    pid_t pid;
    int fd;

    fd = 0;
    args = ft_split(root->args, ' ');
    cmdpath = get_cmd_path(neobash.paths, args[0]);
    // printf("path-[%s]\n", cmdpath);
    pid = fork();
    if (!pid)
    {
        if (root->iol)
        {
            if (root->iol->type == OUT)
                fd = open(root->iol->value, O_CREAT | O_RDWR , 0644);
            if (fd < 0)
                return (2);
            dup2(fd, STDOUT_FILENO);
        }
        execve(cmdpath, args, neobash.envp);
        printf("neobash: command not found: %s\n", args[0]);
        return (127);
    }
    else
    {
        wait(NULL);
        return (0);
    }
    return (0);
}
// bool ft_protect(int (*ft)(void *))
// {
//     if (ft == 0)
// }

void    ex_lpipe(int fd[2], t_node *root)
{
    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);
    neobash.status = execute_ast(root);
}

void    ex_rpipe(int fd[2], t_node *root)
{
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
    neobash.status = execute_ast(root);
}


unsigned int ex_pipes(t_node *root)
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
    {
        ex_lpipe(fd, root->left);
    }
    else
    {
        pid1 = fork();
        if (pid1 < 0)
            return (1);
        if (!pid1)
        {
            ex_rpipe(fd, root->right);
        }
        else
        {
            close(fd[0]);
            close(fd[1]);
            wait(NULL);
            return (neobash.status);
        }
    }
    return (42);
}
unsigned int     execute_ast(t_node *root)
{
    int ex;
    // int fd[2];
    // pid_t pid;
    // pid_t pid1;

    ex = 42;
    // ft_expand_args();
    if (!root)
        return (1);
    if (root->type == PIPE_N)
        return (ex_pipes(root));
    else if (AND_N == root->type)
    {
        ex = execute_ast(root->left);
        if (ex == 0)
            return (execute_ast(root->right));
        return (ex);
    }
    else if (OR_N == root->type)
    {
        ex = execute_ast(root->left);
        if (ex != 0)
            return (execute_ast(root->right));
    }
    else
        return (ex_cmd(root));

    return (ex);
}

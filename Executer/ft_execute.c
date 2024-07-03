/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:08:37 by ajabri            #+#    #+#             */
/*   Updated: 2024/07/03 08:43:44 by ajabri           ###   ########.fr       */
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


unsigned int execute_ast(t_node *root)
{
    int ex;
    int fd[2];
    pid_t pid;
    pid_t pid1;

    ex = 42;
    if (!root)
        return 1337;

    if (root->type == CMD_N)
        return ex_cmd(root);
    else if (root->type == OR_N)
    {
        ex = execute_ast(root->left);
        if (ex != 0)
        {
            ex = execute_ast(root->right);
        }
    }
    else if (root->type == AND_N)
    {
        ex = execute_ast(root->left);
        if (ex == 0)
        {
            ex = execute_ast(root->right);
        }
    }
    else if (root->type == PIPE_N)
    {
        if (pipe(fd) == -1)
            return 2;

        pid = fork();
        if (pid == -1)
            return 2;

        if (pid == 0) // First child
        {
            dup2(fd[1], STDOUT_FILENO);
            close(fd[0]);
            close(fd[1]);
            _exit(execute_ast(root->left));
        }

        pid1 = fork();
        if (pid1 == -1)
            return 2;

        if (pid1 == 0) // Second child
        {
            dup2(fd[0], STDIN_FILENO);
            close(fd[1]);
            close(fd[0]);
            _exit(execute_ast(root->right));
        }

        // Parent process
        close(fd[0]);
        close(fd[1]);
        waitpid(pid, &ex, 0);
        waitpid(pid1, &ex, 0);
    }

    return ex;
}

// unsigned int     execute_ast(t_node *root)
// {
//     int ex;
//     int fd[2];
//     pid_t pid;
//     pid_t pid1;

//     ex = 42;
//     if (!root)
//         return 1337;
//     if (root->type == CMD_N)
//         return (ex_cmd(root));
//     else if (root->type == OR_N)
//     {
//         ex = execute_ast(root->left);
//         if (ex != 0)
//         {
//             // printf("right value `%s'\n", root->right->args);
//             ex = execute_ast(root->right);
//         }
//     }
//     else if (root->type == AND_N)
//     {
//         ex = execute_ast(root->left);
//         ex = execute_ast(root->right);
//     }
//     else if (root->type == PIPE_N)
//     {
//         if (pipe(fd))
//             return (2);
//         pid = fork();
//         if (!pid)
//         {
//             dup2(fd[1], STDOUT_FILENO);
//             close(fd[0]);
//             close(fd[1]);
//             ex = execute_ast(root->left);
//         }
//         pid1 = fork();
//         if (!pid1)
//         {
//             dup2(fd[0], STDIN_FILENO);
//             close(fd[1]);
//             close(fd[0]);
//             ex = execute_ast(root->right);
//         }
//         else
//         {
//             close(fd[1]);
//             close(fd[0]);
//             wait(NULL);
//         }
//     }
//     return (ex);
// }

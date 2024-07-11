/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:08:37 by ajabri            #+#    #+#             */
/*   Updated: 2024/07/11 16:07:17 by kali             ###   ########.fr       */
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

void	heredoc_f(t_io *io, int p[2])
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
			ft_putstr_fd(line, p[1]);
			ft_putstr_fd("\n", p[1]);
		}
	}
	// ft_clean_ms();
	exit(0);
}

void ft_init_io(t_node *root)
{
    int fd[2];
    pid_t pid;
    t_io *io;

    if (!root)
        return;
    // root->exp_val = ft_expand(root->args);
    io = root->iol;
    while (io)
    {
        // printf("[%s]-[%d]\n", io->value, io->type);
        if (io->type == HERE_DOC)
        {
            // printf("Hello \n");
            neobash.hdoc = 0;
            pipe(fd);
            pid = fork();
            if (!pid)
                heredoc_f(io, fd);
            else
                waitpid(pid, NULL, 0);
        }
        // else
        // {
        //     printf("hello else\n");
        //     // io->exp_val = ft_expand(io->value);
        // }
        io = io->next;
    }
}

void ft_before_exec(t_node *root)
{
    t_root_t tp;

    if (!root)
        return;
    tp = root->type;
    if (tp == PIPE_N || tp == OR_N || tp == AND_N)
    {
        ft_before_exec(root->left);
        if (neobash.hdoc)
            ft_before_exec(root->right);
    }
    else
        ft_init_io(root);
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
        if (!ft_strncmp(root->args, "env", 3))
        {
            ft_env(neobash.envl);
            exit(0);
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
    // tcsetattr(STDIN_FILENO, TCSANOW, &neobash.original_term);
    ft_before_exec(neobash.tree);
    neobash.status = ft_executer(neobash.tree);
}


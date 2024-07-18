/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:08:37 by ajabri            #+#    #+#             */
/*   Updated: 2024/07/18 06:28:14 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

char	*get_cmd_path(char **paths, char *cmd)
{
    printf("`%s'\n", cmd);
    if (!cmd)
        return (NULL);
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
//_____________________________________________________________________

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
    ft_before_exec(neobash.tree);
    neobash.status = ft_executer(neobash.tree);
}


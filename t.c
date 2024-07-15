



void set_state(int state)
{
    // 0 no problem
    // 1 is a syntax problem
    // 2 other errors and problems
    neobash.prs_state = state;
}
void ft_skip_tok()
{
    neobash.cur_tok = neobash.cur_tok->next;
}

bool is_pair()
{
    if (!neobash.cur_tok)
        return (false);
    if (neobash.cur_tok->type == OR || neobash.cur_tok->type == AND || neobash.cur_tok->type == PIPE)
        return (true);
    else
        return (false);
}

bool is_io()
{
    if (neobash.cur_tok->type == APPEND || neobash.cur_tok->type == REDIRECT
            || neobash.cur_tok->type == INPUT || neobash.cur_tok->type == HEREDOC)
        return (true);
    else
        return (false);
}

t_node *ft_newnode(t_root_t node_t)
{
    t_node *res;

    res = ft_malloc(sizeof(t_node));
    res->type = node_t;
    res->args = NULL;
    res->left = NULL;
    res->right = NULL;
    res->iol = NULL;
    return (res);
}

char *ft_strjoinc(const char *s1, const char *s2, char c)
{
    char	*res;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
    if ((!c || !ft_strlen(s1) || !ft_strlen(s2)))
    {
        return (ft_strjoin(s1, s2));
    }
	res = ft_malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i++] = c;
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}
t_io *create_io_node(char *val, t_io_t type)
{
    t_io *res;

    res = ft_malloc(sizeof(t_io));
    res->value = ft_strdup(val);
    res->type = type;
    res->next = NULL;
    return (res);
}

t_io_t get_type(t_token_t tk)
{
    if (tk == APPEND)
        return (APP);
    else if (tk == HEREDOC)
        return (HERE_DOC);
    else if (tk == INPUT)
        return (IN);
    // else if (tk == REDIRECT)
    //     return (OUT);
    return (OUT);
}

void ft_addback_io_node(t_io **iop, t_io *new)
{
    t_io *tmp;

    if (!*iop)
    {
        *iop = new;
        return;
    }
    tmp = *iop;
    while (tmp && tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}
bool    create_iol(t_io **io, t_io_t io_t)
{
    t_io *new;

    if (neobash.prs_state)
        return (false);
    while (neobash.cur_tok && is_io())
    {
        ft_skip_tok();
        if (!neobash.cur_tok || neobash.cur_tok->type != WRD)
            return (set_state(1), false);
        new = create_io_node(neobash.cur_tok->value, io_t);
        if (!new)
            return (set_state(2), false);
        ft_addback_io_node(io, new);
        ft_skip_tok();
    }
    return (true);
}

bool ft_argv(char **cmd)
{
    char *tmp;

    if (neobash.prs_state)
        return (NULL);
    if (!*cmd)
        *cmd = ft_strdup("");
    if (!*cmd)
        return (NULL);
    while (neobash.cur_tok && neobash.cur_tok->type == WRD)
    {
        tmp = *cmd;
        *cmd = ft_strjoinc(*cmd, neobash.cur_tok->value, ' ');
        if (!*cmd)
            return (set_state(2), false);
        free(tmp);
        ft_skip_tok();
    }
    return (true);
}


t_node *ft_scmd()
{
    t_node *result;

    if (neobash.prs_state)
        return (NULL);
    result = ft_newnode(CMD_N);
    if (!result)
        return (set_state(2), NULL);
    // result->args = NULL;
    while (neobash.cur_tok && (neobash.cur_tok->type == WRD || is_io()))
    {
        if (neobash.cur_tok->type == WRD)
        {
            if (!ft_argv(&result->args))
                return (set_state(2),NULL);
        }
        else if (is_io())
        {
            // printf(RED"[[[  %d ]]][`%s']\n"RES, neobash.cur_tok->type, neobash.cur_tok->value);
            if (!create_iol(&result->iol, get_type(neobash.cur_tok->type)))
                return (free(result->args), free(result), NULL);
        }
    }
    return (result);
}

t_node *ft_left_hand()
{
    t_node *result;

    if (neobash.prs_state || !neobash.cur_tok)
        return (NULL);
    if (neobash.cur_tok->type == R_PARENT || is_pair())
        return (set_state(1), NULL);
    else if (neobash.cur_tok->type == L_PARENT)
    {
        ft_skip_tok();
        result = ft_rdp(0);
        if (!result)
            return (set_state(2), NULL);
        if (!neobash.cur_tok || neobash.cur_tok->type != R_PARENT)
            return (set_state(1), NULL);
        ft_skip_tok();
        return (result);
    }
    else
        return (ft_scmd());
}

int ft_precedence(t_token_t tp)
{
    if (tp == PIPE)
        return 2;
    else if (tp == OR)
        return 1;
    else if (tp == AND)
        return 0;
    else
        return -1;
}


t_root_t get_node_t(t_token_t tk)
{
    if (tk == PIPE)
        return (PIPE_N);
    else if (tk == AND)
        return (AND_N);
    else if (tk == OR)
        return (OR_N);
    return (NOTHING);
}
t_node *create_pair_node(t_node *left, t_node *right, t_root_t node_t)
{
    t_node *root;

    root = ft_newnode(node_t);
    root->left = left;
    root->right = right;
    return (root);
}

t_node *ft_rdp(int p)
{
    t_node *left;
    t_node *right;
    t_token_t tmp;

    if (neobash.prs_state)
        return (NULL);
    left = ft_left_hand();
    if (!left)
        return (NULL);
    while (is_pair() && ft_precedence(neobash.cur_tok->type) >= p)
    {
        tmp = neobash.cur_tok->type;
        ft_skip_tok();
        if (!neobash.cur_tok)
            return (set_state(1), left);
        neobash.np = ft_precedence(tmp) + 1;
        right = ft_rdp(neobash.np);
        if (!right)
            return (left);
        left = create_pair_node(left, right, get_node_t(tmp));
        if (!left)
            return (NULL); // free here;
    }
    return (left);
}

t_node  *ft_parser()
{
    t_node      *tree_root;

    neobash.cur_tok = neobash.tokens;
    tree_root = ft_rdp(0);
    if (neobash.cur_tok)
        return (set_state(1), tree_root);
    return (tree_root);
}

void    ft_init_neobash(char **env)
{
    // (void)env;
    neobash.envp = env;
    get_env_list(env);
    neobash.prs_state = 0;
    neobash.hdoc = 1;
    neobash.paths = grep_paths(env);
    // neobash.prompt = NULL;
}
/*lldld*/
void    ft_syntax_after()
{
    if (neobash.prs_state == 1)
    {
        if (!neobash.cur_tok)
        {
        printf("neobash: syntax error near unexpected token `%s'\n", "newline");
        // free_tree();
        return ;
        }
        printf("neobash: syntax error near unexpected token `%s'\n", neobash.cur_tok->value);
        // free_tree();
    }
    return;
}

void neoshell()
{
    while (true)
    {
        neobash.line = readline(PROMPT);
        if (neobash.line)
            add_history(neobash.line);
        ft_lexer();
        if (!neobash.tokens)
            continue;
        neobash.tree = ft_parser();
        // print_ast(neobash.tree);
        if (neobash.prs_state)
        {
            ft_syntax_after();
            neobash.prs_state = 0;
            continue;
        }
        // neobash.status = execute_ast(neobash.tree);
        execution();
        printf("Execution result: %d\n", neobash.status);
    }
    ft_free_all();
}
int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    ft_init_neobash(env);
    neoshell();
    return (0);
}

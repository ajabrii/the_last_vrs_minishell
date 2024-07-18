/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: venom <venom@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:41:10 by kali              #+#    #+#             */
/*   Updated: 2024/07/17 17:49:36 by venom            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

g_shell neobash;

// Function to print a single node in the AST
void print_ast_node(t_node *node, int indent) {
    if (node == NULL) {
        return;
    }

    // Print node type
    switch (node->type) {
        case CMD_N:
            printf("%*sCommand Node:\n", indent, "");
            break;
        case PIPE_N:
            printf("%*sPipe Node:\n", indent, "");
            break;
        case AND_N:
            printf("%*sAND Node:\n", indent, "");
            break;
        case OR_N:
            printf("%*sOR Node:\n", indent, "");
            break;
        default:
            printf("%*sUnknown Node Type\n", indent, "");
            break;
    }

    // Print arguments if they exist
    if (node->args != NULL) {
        printf("%*sArguments: %s\n", indent + 2, "", node->args);
    }

    // Print IO redirection list if it exists
    if (node->iol != NULL) {
        printf("%*sIO Redirections:\n", indent + 2, "");
        t_io *io_node = node->iol;
        while (io_node != NULL) {
            printf("%*sType: ", indent + 4, "");
            switch (io_node->type) {
                case IN:
                    printf("Input\n");
                    break;
                case OUT:
                    printf("Output\n");
                    break;
                case HERE_DOC:
                    printf("Heredoc\n");
                    break;
                case APP:
                    printf("Append\n");
                    break;
                default:
                    printf("Unknown\n");
                    break;
            }
            printf("%*sValue: %s\n", indent + 4, "", io_node->value);
            io_node = io_node->next;
        }
    }

    // Recursively print left and right children
    if (node->left != NULL) {
        printf("%*sLeft Child:\n", indent + 2, "");
        print_ast_node(node->left, indent + 4);
    }

    if (node->right != NULL) {
        printf("%*sRight Child:\n", indent + 2, "");
        print_ast_node(node->right, indent + 4);
    }
}

// Function to print the entire AST
void print_ast(t_node *root) {
    if (root == NULL) {
        printf("Syntax Tree is empty.\n");
        return;
    }

    printf("Printing Abstract Syntax Tree:\n");
    print_ast_node(root, 0);
}

/*88888888888888*/
void    ft_init_neobash(char **env)
{
    // (void)env;
    neobash.envp = env;
    get_env_list(env);
    neobash.prs_state = 0;
    neobash.hdoc = 1;
    neobash.flag = 0;
    neobash.in = dup(0);
	neobash.out = dup(1);
    neobash.paths = grep_paths(env);
    neobash.level = 1;
    // neobash.prompt = NULL;
}
/*lldld*/
void    ft_syntax_after()
{
    int flag;

    flag = 0;
    if (neobash.prs_state == 1)
    {
        if (!neobash.cur_tok)
        {
            printf("neobash: syntax error near unexpected token `%s'\n", "newline");
            // free_tree();
            return ;
        }
        if (neobash.flag == 1 && is_io(neobash.cur_tok->next->type))
        {
            neobash.prs_state = 0;
            flag = 1;
        }
        if (!flag)
        {
            // printf(RED "[%s]-[%d]--[%d]\n" RES, neobash.cur_tok->value, neobash.cur_tok->type, neobash.flag);
            printf("neobash: syntax error near unexpected token `%s'\n", neobash.cur_tok->value);
            // free_tree();
        }
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
        // printf(RED "[%s]-[%d]\n" RES, neobash.cur_tok->value, neobash.cur_tok->type);
        if (neobash.prs_state)
        {
            ft_syntax_after();
            // printf("HEre\n");
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
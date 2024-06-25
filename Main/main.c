/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:41:10 by kali              #+#    #+#             */
/*   Updated: 2024/06/25 19:04:14 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/headers.h"

g_shell neobash;




void print_spaces(int num_spaces) {
    for (int i = 0; i < num_spaces; ++i) {
        putchar(' ');
    }
}

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
/*/***************************** */
void    ft_init_neobash(char **env)
{
    // get_env_list(env);
    neobash.prs_state = 0;
    // neobash.prompt = NULL;
}

void neoshell()
{
    while (true)
    {
        neobash.line = readline(PROMPT);
        if (neobash.line)
            add_history(neobash.line);
        neobash.tokens = ft_lexer();
        if (!neobash.tokens)
            continue;
        neobash.tree = ft_parser();
        print_ast(neobash.tree);
        if (neobash.prs_state)
        {
            // ft_syntax();
            continue;
        }
        // ft_execute();
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
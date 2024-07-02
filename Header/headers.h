/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:41:39 by kali              #+#    #+#             */
/*   Updated: 2024/07/02 05:52:25 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef HEADERS_H
# define HEADERS_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <limits.h>
# include "../Libft/libft.h"

/*colors*/
# define RED "\033[30;31m"
# define G "\033[1;32m"
# define ORG "\033[1;33m"
# define PER "\033[97m"
# define CY "\033[96m"
# define RES "\033[0m"

#define PROMPT G "🌟::NeoShell~/💎[" ORG "Prompt" RES G "]🗿$\n|~↠$ " RES
/*env list*/
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;
/*/env list*/

/*token type enums*/
typedef enum s_token_t
{
    WRD, // Word cmd file etc ..
	INPUT,
	APPEND,
	HEREDOC,
	REDIRECT,
	L_PARENT,
	R_PARENT,
    //STAR,
	AND,
	OR,
	PIPE,
    SYNTAX
}t_token_t;

/*token list*/
typedef struct s_token
{
    char *value;
    t_token_t type;
    struct s_token *next;
}   t_token;
/*************************** */
typedef enum s_io_t
{
    OUT,
    IN,
    HERE_DOC,
    APP, //append
} t_io_t;

/*this is the input output type*/
typedef struct s_io
{
    t_io_t type;
    int here_doc;
    char *value;
    char **exp_val;
    struct s_io *next;
} t_io;
/*************************** */

/*this is for node types*/
typedef enum s_node_t
{
    AND_N,
    OR_N,
    PIPE_N,
    CMD_N,
    IO_N,
    NOTHING // this is just for return function
} t_root_t;
/*this struct is the node that compose the tree AST*/
typedef struct s_node
{
    t_root_t        type;
    t_io            *iol; // input/output
    char            *args; // the name cmdargs is better
    char            **exp_val;
    struct s_node *left;
    struct s_node *right;
} t_node;

typedef  struct s_leak
{
    void            *address;
    struct s_leak   *next;
}               t_leak;


/*the global struct*/

typedef struct s_shell
{
    char            *line;
    int             np;
    t_token         *tokens;
    t_token			*cur_tok;
	t_node			*tree;
    int             status;
    int             prs_state;
    char            **envp;
    char            **sub;
    // char            *prompt;
    t_env           *envl;
    t_leak          *leaks;
} g_shell;

extern g_shell neobash;

/* <Builtins/env.c> */
void        get_env_list(char **env);
t_leak      *ft_leaks_lstlast(t_leak *lst);
void        ft_leaks_lstadd_back(t_leak **lst, t_leak *newx);
t_leak      *ft_leaks_lstnew(void *var);
void        *ft_malloc(size_t size);
t_leak      *ft_lstlastv2(t_leak *lst);
/* </Builtins/env.c> */

/* <Lexer/lexixal.c> */
void ft_lexer();
void    give_token();
void ft_coutquotes();
void ft_err(char *err, int flag);
// int ft_token_sp(t_token **tokens, char **line);
/* </Lexer/lexixal.c> */

/* <Lexer/lex_utils.c> */
bool check_spcial(char c);
bool check_red_or_and(char *line, int i);
void ft_lstadd_backv3(t_token **lst, t_token *newx);
t_token	*ft_lstnewv3(char *var, t_token_t token);
t_token	*ft_lstlastv3(t_token *lst);
/* </Lexer/lex_utils.c> */

/* <Lexer/token.c> */
t_token_t set_token(int i);
bool is_whitespaces(char line);
int count_whitespaces(char *line, int i);
int count_inside_quotes(int i, char q);
bool is_quotition(char i);
/* </Lexer/token.c> */

/* <Lexer/lextools.c> */
void ft_lexical();
/* <Lexer/lextools.c> */

/* <Leaks/garbedge.c> */
void *ft_malloc(size_t size);
/* <Leaks/garbedge.c> */

/* <Leaks/free_all.c> */
void      ft_free_all();
/* </Leaks/free_all.c> */

/* <Parsing/ft_parsing.c> */
t_node *ft_parser();
bool ft_argv(char **cmd);
t_node *ft_scmd();
t_node *ft_left_hand();
t_node *ft_rdp(int p);
int ft_precedence(t_token_t tp);
/* </Parsing/ft_parsing.c> */

/* <Parsing/tools.c> */
bool is_pair();
bool is_io();
void ft_skip_tok();
void set_state(int state);
t_node *ft_newnode(t_root_t node_t);
/* </Parsing/tools.c> */

/* <Parsing/putils.c> */
char    *ft_strjoinc(const char *s1, const char *s2, char c);
bool    create_iol(t_io **io, t_io_t io_t);
t_io    *create_io_node(char *val, t_io_t type);
t_io_t  get_type(t_token_t tk);
void    ft_addback_io_node(t_io **iop, t_io *new);
/* </Parsing/putils.c> */

/* <Builtins> */
void    ft_env(t_env *env);
void ft_exit(int ex);
/* </Builtins> */

/* <Executer/ft_executer.c> */
void ft_executer();
/* </Executer/ft_executer.c> */


#endif
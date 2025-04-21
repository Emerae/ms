#ifndef STRUCTS_H
#define STRUCTS_H

#include "minishell.h"

typedef struct s_shell
{
	t_list *env;             // Linked list of t_env
	/*
	struct s_tree *ast;      // Syntax tree
	int last_exit_code;      // Result of last command
	int should_exit;         // Set when exit is called
	int input_fd;            // Default input (STDIN)
	int output_fd;           // Default output (STDOUT)
	*/
} t_shell;

typedef struct s_env
{
	char	*var;
	char	*value;
	bool	is_exported;
} t_env;

typedef struct s_redir {
    int				type;      // 0: < | 1: > | 2: >> | 3: <<
    char			*file;
    struct s_redir	*next;
} t_redir;

typedef struct s_cmd {
    char			**args;        // ["ls", "-l", NULL]
    t_redir			*redirs;    // liste de redirections
    int				builtin_id;     // -1 si c’est pas un builtin
    struct s_cmd	*next; // pour les pipes
} t_cmd;
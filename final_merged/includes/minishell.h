/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:00:00 by anonymous         #+#    #+#             */
/*   Updated: 2025/04/22 12:00:00 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

/* Token types */
# define WORD 1
# define PIPE 2
# define REDIR_IN 3
# define REDIR_OUT 4
# define REDIR_APPEND 5
# define REDIR_HEREDOC 6
# define HEREDOC_DELIM 7

/* Global variable for signal handling only */
extern int	g_sig_status;

/* Structures */
typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	char			*file;
	int				type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	t_env			*env;
	struct s_cmd	*cmd_list;
	char			*input;
	int				exit;
	int				exit_status;
}	t_data;

typedef struct s_cmd
{
	t_token			*args;
	t_redir			*redirections;
	struct s_cmd	*next;
	t_data			*data;
}	t_cmd;

/* Initialization */
t_data	*init_data(char **envp);
void	init_shell(t_data *data);

/* Parsing */
int		parse_input(t_data *data);
t_token	*tokenize(char *input);
t_cmd	*create_cmd_list(t_token *tokens, t_data *data);
void	expand_tokens(t_token *tokens, t_data *data);

/* Execution */
void	execute_cmd(t_cmd *cmd, t_data *data);
void	execute_pipeline(t_cmd *cmd, t_data *data);
int		setup_redirections(t_cmd *cmd);
void	handle_cmd_child(t_cmd *cmd, t_data *data);
char	**prepare_cmd_args(t_cmd *cmd);

/* Builtins */
int		is_builtin(char *cmd);
void	execute_builtin(t_cmd *cmd, t_data *data);
int		builtin_echo(char **args);
int		builtin_cd(char **args, t_data *data);
int		builtin_pwd(void);
int		builtin_export(char **args, t_data *data);
int		builtin_unset(char **args, t_data *data);
int		builtin_env(t_data *data);
int		builtin_exit(char **args, t_data *data);

/* Environment */
t_env	*init_env(char **envp);
t_env	*create_env_node(char *key, char *value);
void	add_env_node(t_env **env, t_env *new_node);
char	*get_env_key(char *str);
char	*get_env_value_from_str(char *str);
t_env	*get_env_node(t_env *env, char *key);
char	*get_env_value(t_env *env, char *key);
void	set_env_var(t_env *env, char *key, char *value);
void	remove_env_var(t_env *env, char *key);
int		count_env_vars(t_env *env);
char	**convert_env_to_array(t_env *env);
void	free_env(t_env *env);
char	**get_paths(char **envp);

/* Utils */
void	free_array(char **array);
void	print_error(char *cmd, char *message, char *arg);
void	exit_shell(t_data *data, int exit_code);
void	free_cmds(t_cmd *cmd_list);
void	free_token_list(t_token *tokens);
void	free_redirections(t_redir *redirections);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_charjoin(char *s1, char c);

/* Signals */
void	setup_signals(void);
void	setup_signals_child(void);

#endif

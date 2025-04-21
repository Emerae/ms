/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:00:00 by student           #+#    #+#             */
/*   Updated: 2023/09/22 12:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "structs.h"

/* Main functions */
void	init_shell(t_shell *shell, char **envp);
void	exit_shell(t_shell *shell, int exit_code);

/* Lexer functions */
t_token	*tokenize_input(char *input);
t_token	*create_token(char *content, t_token_type type);
void	add_token(t_token **tokens, t_token *new_token);
char	*extract_token(char *input, int *i);
int		handle_quotes(char *input, int *i, char quote);
t_token_type	identify_token_type(char *str);

/* Parser functions */
t_cmd	*parse_tokens(t_shell *shell);
t_cmd	*create_cmd(void);
int		add_arg(t_cmd *cmd, char *arg);
int		add_redir(t_cmd *cmd, int type, char *file);
char	*expand_vars(t_shell *shell, char *str);
char	*remove_quotes(char *str);

/* Executor functions */
int		execute_cmds(t_shell *shell);
int		execute_cmd(t_shell *shell, t_cmd *cmd, int in_fd, int out_fd);
int		apply_redirections(t_cmd *cmd, int *in_fd, int *out_fd);
int		handle_heredoc(t_shell *shell, char *delimiter);
int		is_builtin(char *cmd);
int		execute_builtin(t_shell *shell, t_cmd *cmd);
char	*find_cmd_path(t_shell *shell, char *cmd);

/* Builtin functions */
int		builtin_echo(t_cmd *cmd);
int		builtin_cd(t_shell *shell, t_cmd *cmd);
int		builtin_pwd(void);
int		builtin_export(t_shell *shell, t_cmd *cmd);
int		builtin_unset(t_shell *shell, t_cmd *cmd);
int		builtin_env(t_shell *shell);
int		builtin_exit(t_shell *shell, t_cmd *cmd);

/* Environment functions */
t_env	*create_env_list(char **envp);
char	**create_env_array(t_env *env);
char	*get_env_value(t_shell *shell, char *key);
int		set_env_value(t_shell *shell, char *key, char *value);
int		unset_env_value(t_shell *shell, char *key);

/* Signal functions */
void	setup_signals(void);
void	handle_sigint(int sig);
void	handle_sigquit(int sig);

/* Utils functions */
void	free_tokens(t_token *tokens);
void	free_cmds(t_cmd *cmds);
void	free_env(t_env *env);
void	free_array(char **array);
int		ft_isspace(char c);
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_strncpy(char *dest, char *src, size_t n);

#endif

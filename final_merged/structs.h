/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:00:00 by student           #+#    #+#             */
/*   Updated: 2023/09/22 12:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

/* Définition des types de tokens */
typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC,
	T_END
}	t_token_type;

/* Structure pour les tokens */
typedef struct s_token
{
	char			*content;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

/* Structure pour les redirections */
typedef struct s_redir
{
	int				type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

/* Structure pour les commandes */
typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

/* Structure pour l'environnement */
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/* Structure principale du minishell */
typedef struct s_shell
{
	t_token			*tokens;
	t_cmd			*cmds;
	t_env			*env;
	char			**env_array;
	int				status;
	int				in_cmd;
	int				heredoc_active;
	int				exit_status;
}	t_shell;

#endif

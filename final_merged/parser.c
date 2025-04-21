/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:00:00 by student           #+#    #+#             */
/*   Updated: 2023/09/22 12:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

int	add_arg(t_cmd *cmd, char *arg)
{
	int		i;
	int		size;
	char	**new_args;

	size = 0;
	if (cmd->args)
	{
		while (cmd->args[size])
			size++;
	}
	new_args = (char **)malloc(sizeof(char *) * (size + 2));
	if (!new_args)
		return (0);
	i = 0;
	while (i < size)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[i] = ft_strdup(arg);
	if (!new_args[i])
		return (free(new_args), 0);
	new_args[i + 1] = NULL;
	if (cmd->args)
		free(cmd->args);
	cmd->args = new_args;
	return (1);
}

int	add_redir(t_cmd *cmd, int type, char *file)
{
	t_redir	*new_redir;
	t_redir	*current;

	new_redir = (t_redir *)malloc(sizeof(t_redir));
	if (!new_redir)
		return (0);
	new_redir->type = type;
	new_redir->file = ft_strdup(file);
	if (!new_redir->file)
		return (free(new_redir), 0);
	new_redir->next = NULL;
	if (!cmd->redirs)
	{
		cmd->redirs = new_redir;
		return (1);
	}
	current = cmd->redirs;
	while (current->next)
		current = current->next;
	current->next = new_redir;
	return (1);
}

t_cmd	*parse_tokens(t_shell *shell)
{
	t_cmd	*cmds;
	t_cmd	*current_cmd;
	t_token	*token;

	cmds = create_cmd();
	if (!cmds)
		return (NULL);
	current_cmd = cmds;
	token = shell->tokens;
	while (token)
	{
		if (token->type == T_PIPE)
		{
			current_cmd->next = create_cmd();
			if (!current_cmd->next)
				return (free_cmds(cmds), NULL);
			current_cmd = current_cmd->next;
		}
		else if (token->type == T_REDIR_IN || token->type == T_REDIR_OUT
			|| token->type == T_APPEND || token->type == T_HEREDOC)
		{
			token = token->next;
			if (!token || token->type != T_WORD)
				return (free_cmds(cmds), NULL);
			if (!add_redir(current_cmd, token->type, token->content))
				return (free_cmds(cmds), NULL);
		}
		else if (token->type == T_WORD)
		{
			char *expanded = expand_vars(shell, token->content);
			if (!expanded)
				return (free_cmds(cmds), NULL);
			if (!add_arg(current_cmd, expanded))
				return (free(expanded), free_cmds(cmds), NULL);
			free(expanded);
		}
		token = token->next;
	}
	return (cmds);
}

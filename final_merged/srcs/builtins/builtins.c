/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:00:00 by anonymous         #+#    #+#             */
/*   Updated: 2025/04/22 12:00:00 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

void	execute_builtin(t_cmd *cmd, t_data *data)
{
	char	**args;

	args = prepare_cmd_args(cmd);
	if (!args || !args[0])
	{
		free_array(args);
		return ;
	}
	if (ft_strcmp(args[0], "echo") == 0)
		data->exit_status = builtin_echo(args);
	else if (ft_strcmp(args[0], "cd") == 0)
		data->exit_status = builtin_cd(args, data);
	else if (ft_strcmp(args[0], "pwd") == 0)
		data->exit_status = builtin_pwd();
	else if (ft_strcmp(args[0], "export") == 0)
		data->exit_status = builtin_export(args, data);
	else if (ft_strcmp(args[0], "unset") == 0)
		data->exit_status = builtin_unset(args, data);
	else if (ft_strcmp(args[0], "env") == 0)
		data->exit_status = builtin_env(data);
	else if (ft_strcmp(args[0], "exit") == 0)
		data->exit_status = builtin_exit(args, data);
	free_array(args);
}

char	**prepare_cmd_args(t_cmd *cmd)
{
	char	**args;
	int		i;
	t_token	*token;

	i = 0;
	token = cmd->args;
	while (token)
	{
		i++;
		token = token->next;
	}
	args = (char **)malloc(sizeof(char *) * (i + 1));
	if (!args)
		return (NULL);
	i = 0;
	token = cmd->args;
	while (token)
	{
		args[i] = ft_strdup(token->value);
		i++;
		token = token->next;
	}
	args[i] = NULL;
	return (args);
}

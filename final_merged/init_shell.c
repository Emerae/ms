/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:00:00 by student           #+#    #+#             */
/*   Updated: 2023/09/22 12:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *shell, char **envp)
{
	ft_memset(shell, 0, sizeof(t_shell));
	shell->env = create_env_list(envp);
	shell->env_array = create_env_array(shell->env);
	shell->exit_status = 0;
	shell->in_cmd = 0;
	shell->heredoc_active = 0;
}

void	exit_shell(t_shell *shell, int exit_code)
{
	if (shell->tokens)
		free_tokens(shell->tokens);
	if (shell->cmds)
		free_cmds(shell->cmds);
	if (shell->env)
		free_env(shell->env);
	if (shell->env_array)
		free_array(shell->env_array);
	rl_clear_history();
	exit(exit_code);
}

t_env	*create_env_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	if (!new_node->key)
	{
		free(new_node);
		return (NULL);
	}
	if (value)
	{
		new_node->value = ft_strdup(value);
		if (!new_node->value)
		{
			free(new_node->key);
			free(new_node);
			return (NULL);
		}
	}
	else
		new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}

t_env	*create_env_list(char **envp)
{
	t_env	*env_list;
	t_env	*new_node;
	t_env	*current;
	int		i;
	char	*equals_sign;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		equals_sign = ft_strchr(envp[i], '=');
		if (equals_sign)
		{
			*equals_sign = '\0';
			new_node = create_env_node(envp[i], equals_sign + 1);
			*equals_sign = '=';
			if (!new_node)
				return (free_env(env_list), NULL);
			if (!env_list)
				env_list = new_node;
			else
			{
				current = env_list;
				while (current->next)
					current = current->next;
				current->next = new_node;
			}
		}
		i++;
	}
	return (env_list);
}

char	**create_env_array(t_env *env)
{
	char	**env_array;
	t_env	*current;
	int		size;
	int		i;
	char	*temp;

	size = 0;
	current = env;
	while (current)
	{
		size++;
		current = current->next;
	}
	env_array = (char **)malloc(sizeof(char *) * (size + 1));
	if (!env_array)
		return (NULL);
	current = env;
	i = 0;
	while (current)
	{
		if (current->value)
		{
			temp = ft_strjoin(current->key, "=");
			if (!temp)
				return (free_array(env_array), NULL);
			env_array[i] = ft_strjoin(temp, current->value);
			free(temp);
			if (!env_array[i])
				return (free_array(env_array), NULL);
		}
		else
			env_array[i] = ft_strdup(current->key);
		current = current->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

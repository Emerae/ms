/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:00:00 by anonymous         #+#    #+#             */
/*   Updated: 2025/04/22 12:00:00 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*get_env_node(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

char	*get_env_value(t_env *env, char *key)
{
	t_env	*node;

	node = get_env_node(env, key);
	if (node)
		return (node->value);
	return (NULL);
}

void	set_env_var(t_env *env, char *key, char *value)
{
	t_env	*node;

	node = get_env_node(env, key);
	if (node)
	{
		if (node->value)
			free(node->value);
		if (value)
			node->value = ft_strdup(value);
		else
			node->value = NULL;
	}
	else
	{
		node = create_env_node(ft_strdup(key), value ? ft_strdup(value) : NULL);
		if (node)
			add_env_node(&env, node);
	}
}

void	remove_env_var(t_env *env, char *key)
{
	t_env	*prev;
	t_env	*curr;

	prev = NULL;
	curr = env;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				env = curr->next;
			free(curr->key);
			if (curr->value)
				free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	count_env_vars(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

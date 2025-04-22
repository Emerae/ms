/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:00:00 by anonymous         #+#    #+#             */
/*   Updated: 2025/04/22 12:00:00 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*init_env(char **envp)
{
	t_env	*env;
	t_env	*new_node;
	char	*key;
	char	*value;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		key = get_env_key(envp[i]);
		value = get_env_value_from_str(envp[i]);
		new_node = create_env_node(key, value);
		if (new_node)
			add_env_node(&env, new_node);
		else
		{
			free(key);
			free(value);
		}
		i++;
	}
	return (env);
}

t_env	*create_env_node(char *key, char *value)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	add_env_node(t_env **env, t_env *new_node)
{
	t_env	*last;

	if (!*env)
	{
		*env = new_node;
		return ;
	}
	last = *env;
	while (last->next)
		last = last->next;
	last->next = new_node;
}

char	*get_env_key(char *str)
{
	int		i;
	char	*key;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	key = (char *)malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	ft_strlcpy(key, str, i + 1);
	return (key);
}

char	*get_env_value_from_str(char *str)
{
	int		i;
	char	*value;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (NULL);
	value = ft_strdup(str + i + 1);
	return (value);
}

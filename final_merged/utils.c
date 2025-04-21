/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:00:00 by student           #+#    #+#             */
/*   Updated: 2023/09/22 12:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r');
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;
	
	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

char	*ft_strncpy(char *dest, char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*get_env_value(t_shell *shell, char *key)
{
	t_env	*current;

	current = shell->env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

int	set_env_value(t_shell *shell, char *key, char *value)
{
	t_env	*current;
	t_env	*new_node;

	current = shell->env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (current->value)
				free(current->value);
			if (value)
				current->value = ft_strdup(value);
			else
				current->value = NULL;
			if (value && !current->value)
				return (0);
			free_array(shell->env_array);
			shell->env_array = create_env_array(shell->env);
			if (!shell->env_array)
				return (0);
			return (1);
		}
		current = current->next;
	}
	new_node = create_env_node(key, value);
	if (!new_node)
		return (0);
	current = shell->env;
	while (current->next)
		current = current->next;
	current->next = new_node;
	free_array(shell->env_array);
	shell->env_array = create_env_array(shell->env);
	if (!shell->env_array)
		return (0);
	return (1);
}

int	unset_env_value(t_shell *shell, char *key)
{
	t_env	*current;
	t_env	*prev;
	t_env	*to_delete;

	current = shell->env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				shell->env = current->next;
			to_delete = current;
			free(to_delete->key);
			if (to_delete->value)
				free(to_delete->value);
			free(to_delete);
			free_array(shell->env_array);
			shell->env_array = create_env_array(shell->env);
			if (!shell->env_array)
				return (0);
			return (1);
		}
		prev = current;
		current = current->next;
	}
	return (1);
}

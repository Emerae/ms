/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:00:00 by anonymous         #+#    #+#             */
/*   Updated: 2025/04/22 12:00:00 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**convert_env_to_array(t_env *env)
{
	char	**env_array;
	char	*tmp;
	int		count;
	int		i;
	t_env	*curr;

	count = count_env_vars(env);
	env_array = (char **)malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	i = 0;
	curr = env;
	while (curr)
	{
		if (curr->value)
		{
			tmp = ft_strjoin(curr->key, "=");
			env_array[i] = ft_strjoin(tmp, curr->value);
			free(tmp);
			i++;
		}
		curr = curr->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

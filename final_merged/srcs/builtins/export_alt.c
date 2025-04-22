/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:00:00 by anonymous         #+#    #+#             */
/*   Updated: 2025/04/22 12:00:00 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_sorted_env(t_env *env)
{
	t_env	**sorted;
	int		count;
	int		i;
	int		j;
	t_env	*temp;

	count = count_env_vars(env);
	sorted = (t_env **)malloc(sizeof(t_env *) * count);
	if (!sorted)
		return ;
	i = 0;
	temp = env;
	while (temp)
	{
		sorted[i++] = temp;
		temp = temp->next;
	}
	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(sorted[j]->key, sorted[j + 1]->key) > 0)
			{
				temp = sorted[j];
				sorted[j] = sorted[j + 1];
				sorted[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < count)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(sorted[i]->key, STDOUT_FILENO);
		if (sorted[i]->value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(sorted[i]->value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
	free(sorted);
}

static int	is_valid_env_key(char *key)
{
	int	i;

	if (!key || !*key || ft_isdigit(*key))
		return (0);
	i = 0;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	export_var(char *arg, t_data *data)
{
	char	*equal_pos;
	char	*key;
	char	*value;
	int		status;

	equal_pos = ft_strchr(arg, '=');
	if (!equal_pos)
	{
		if (!is_valid_env_key(arg))
		{
			print_error("export", "not a valid identifier", arg);
			return (1);
		}
		if (!get_env_node(data->env, arg))
			set_env_var(data->env, arg, NULL);
		return (0);
	}
	*equal_pos = '\0';
	key = arg;
	value = equal_pos + 1;
	if (!is_valid_env_key(key))
	{
		print_error("export", "not a valid identifier", key);
		*equal_pos = '=';
		return (1);
	}
	set_env_var(data->env, key, value);
	*equal_pos = '=';
	return (0);
}

int	builtin_export(char **args, t_data *data)
{
	int	i;
	int	status;

	if (!args[1])
	{
		print_sorted_env(data->env);
		return (0);
	}
	status = 0;
	i = 1;
	while (args[i])
	{
		if (export_var(args[i], data) != 0)
			status = 1;
		i++;
	}
	return (status);
}

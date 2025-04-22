void	ft_print_sorted_env(t_env *env_list)
{
	t_env	**arr;
	t_env	*tmp;
	int		i;
	int		j;
	int		size;

	size = ft_env_size(env_list);
	arr = (t_env **)malloc(sizeof(t_env *) * (size + 1));
	if (!arr)
		return ;
	i = 0;
	tmp = env_list;
	while (tmp)
	{
		arr[i++] = tmp;
		tmp = tmp->next;
	}
	arr[i] = NULL;
	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(arr[i]->key, arr[j]->key) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (arr[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(arr[i]->key, STDOUT_FILENO);
		if (arr[i]->value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(arr[i]->value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
	free(arr);
}

int	ft_is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0] || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_builtin_export(t_command *cmd, t_env *env_list)
{
	int		i;
	char	*key;
	char	*value;
	char	*equals;

	if (!cmd->argv[1])
	{
		ft_print_sorted_env(env_list);
		return (0);
	}
	i = 1;
	while (cmd->argv[i])
	{
		if (!ft_is_valid_identifier(cmd->argv[i]))
		{
			ft_error_msg("export", "not a valid identifier", 1);
			i++;
			continue ;
		}
		equals = ft_strchr(cmd->argv[i], '=');
		if (equals)
		{
			*equals = '\0';
			key = ft_strdup(cmd->argv[i]);
			value = ft_strdup(equals + 1);
			*equals = '=';
			ft_setenv(env_list, key, value);
			free(key);
			free(value);
		}
		else
		{
			if (!ft_getenv(env_list, cmd->argv[i]))
				ft_setenv(env_list, cmd->argv[i], NULL);
		}
		i++;
	}
	return (0);
}

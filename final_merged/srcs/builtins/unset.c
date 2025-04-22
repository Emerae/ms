int	ft_builtin_unset(t_command *cmd, t_env *env_list)
{
	int	i;

	i = 1;
	while (cmd->argv[i])
	{
		if (!ft_is_valid_identifier(cmd->argv[i]))
		{
			ft_error_msg("unset", "not a valid identifier", 1);
			i++;
			continue ;
		}
		ft_unsetenv(env_list, cmd->argv[i]);
		i++;
	}
	return (0);
}

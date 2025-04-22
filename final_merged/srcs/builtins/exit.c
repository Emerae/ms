int	ft_builtin_exit(t_command *cmd)
{
	long	exit_code;
	int		i;

	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (!cmd->argv[1])
		exit(g_status);
	i = 0;
	if (cmd->argv[1][0] == '-' || cmd->argv[1][0] == '+')
		i++;
	while (cmd->argv[1][i])
	{
		if (!ft_isdigit(cmd->argv[1][i]))
		{
			ft_error_msg("exit", "numeric argument required", 255);
			exit(255);
		}
		i++;
	}
	exit_code = ft_atoi(cmd->argv[1]);
	if (cmd->argv[2])
	{
		ft_error_msg("exit", "too many arguments", 1);
		return (1);
	}
	exit((unsigned char)exit_code);
}

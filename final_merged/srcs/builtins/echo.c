int	ft_builtin_echo(t_command *cmd)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (cmd->argv[i] && ft_strcmp(cmd->argv[i], "-n") == 0)
	{
		n_flag = 1;
		i++;
	}
	while (cmd->argv[i])
	{
		ft_putstr_fd(cmd->argv[i], STDOUT_FILENO);
		if (cmd->argv[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

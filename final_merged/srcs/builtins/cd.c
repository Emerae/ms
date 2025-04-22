int	ft_builtin_cd(t_command *cmd, t_env *env_list)
{
	char	*path;
	char	*oldpwd;
	char	cwd[PATH_MAX];

	if (!cmd->argv[1] || ft_strcmp(cmd->argv[1], "~") == 0)
		path = ft_getenv(env_list, "HOME");
	else
		path = cmd->argv[1];
	if (!path)
		return (ft_error_msg("cd", "HOME not set", 1));
	if (getcwd(cwd, PATH_MAX) != NULL)
		oldpwd = ft_strdup(cwd);
	else
		oldpwd = ft_strdup("");
	if (chdir(path) != 0)
	{
		free(oldpwd);
		return (ft_error_msg(path, "No such file or directory", 1));
	}
	ft_setenv(env_list, "OLDPWD", oldpwd);
	free(oldpwd);
	if (getcwd(cwd, PATH_MAX) != NULL)
		ft_setenv(env_list, "PWD", cwd);
	return (0);
}

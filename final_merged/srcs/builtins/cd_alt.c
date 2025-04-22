/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:00:00 by anonymous         #+#    #+#             */
/*   Updated: 2025/04/22 12:00:00 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	update_pwd_vars(t_data *data)
{
	char	*old_pwd;
	char	*new_pwd;
	char	cwd[4096];

	old_pwd = get_env_value(data->env, "PWD");
	if (old_pwd)
		set_env_var(data->env, "OLDPWD", old_pwd);
	if (getcwd(cwd, 4096))
		set_env_var(data->env, "PWD", cwd);
}

static char	*get_home_dir(t_data *data)
{
	char	*home;

	home = get_env_value(data->env, "HOME");
	if (!home)
	{
		print_error("cd", "HOME not set", NULL);
		return (NULL);
	}
	return (home);
}

int	builtin_cd(char **args, t_data *data)
{
	char	*path;

	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		path = get_home_dir(data);
		if (!path)
			return (1);
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		path = get_env_value(data->env, "OLDPWD");
		if (!path)
		{
			print_error("cd", "OLDPWD not set", NULL);
			return (1);
		}
		ft_putendl_fd(path, STDOUT_FILENO);
	}
	else
		path = args[1];
	if (chdir(path) == -1)
	{
		print_error("cd", strerror(errno), args[1]);
		return (1);
	}
	update_pwd_vars(data);
	return (0);
}

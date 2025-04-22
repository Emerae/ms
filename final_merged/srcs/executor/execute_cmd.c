/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:00:00 by anonymous         #+#    #+#             */
/*   Updated: 2025/04/22 12:00:00 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*find_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*part_path;
	int		i;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	paths = get_paths(envp);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK | X_OK) == 0)
		{
			free_array(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_array(paths);
	return (NULL);
}

static char	**get_paths(char **envp)
{
	char	**paths;
	char	*env_path;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			env_path = envp[i] + 5;
			paths = ft_split(env_path, ':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}

static void	handle_cmd_child(t_cmd *cmd, t_data *data)
{
	char	*path;
	char	**cmd_args;
	char	**envp;

	cmd_args = prepare_cmd_args(cmd);
	if (!cmd_args || !cmd_args[0])
	{
		free_array(cmd_args);
		exit_shell(data, 1);
	}
	if (is_builtin(cmd_args[0]))
	{
		execute_builtin(cmd, data);
		free_array(cmd_args);
		exit_shell(data, g_exit_status);
	}
	envp = convert_env_to_array(data->env);
	path = find_cmd_path(cmd_args[0], envp);
	if (!path)
	{
		print_error(cmd_args[0], "command not found", NULL);
		free_array(cmd_args);
		free_array(envp);
		exit_shell(data, 127);
	}
	execve(path, cmd_args, envp);
	free(path);
	free_array(cmd_args);
	free_array(envp);
	exit_shell(data, 1);
}

static void	execute_single_cmd(t_cmd *cmd, t_data *data)
{
	pid_t	pid;
	int		status;

	if (is_builtin(cmd->args[0]))
	{
		execute_builtin(cmd, data);
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		print_error("fork", "fork failed", NULL);
		return ;
	}
	if (pid == 0)
	{
		setup_redirections(cmd);
		handle_cmd_child(cmd, data);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_status = 128 + WTERMSIG(status);
	}
}

void	execute_cmd(t_cmd *cmd, t_data *data)
{
	if (!cmd)
		return ;
	if (cmd->next == NULL)
		execute_single_cmd(cmd, data);
	else
		execute_pipeline(cmd, data);
}

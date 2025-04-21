/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:00:00 by student           #+#    #+#             */
/*   Updated: 2023/09/22 12:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal_status;

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	execute_builtin(t_shell *shell, t_cmd *cmd)
{
	char	*cmd_name;

	cmd_name = cmd->args[0];
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (builtin_echo(cmd));
	if (ft_strcmp(cmd_name, "cd") == 0)
		return (builtin_cd(shell, cmd));
	if (ft_strcmp(cmd_name, "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(cmd_name, "export") == 0)
		return (builtin_export(shell, cmd));
	if (ft_strcmp(cmd_name, "unset") == 0)
		return (builtin_unset(shell, cmd));
	if (ft_strcmp(cmd_name, "env") == 0)
		return (builtin_env(shell));
	if (ft_strcmp(cmd_name, "exit") == 0)
		return (builtin_exit(shell, cmd));
	return (1);
}

char	*find_cmd_path(t_shell *shell, char *cmd)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;

	if (!cmd || ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_env = get_env_value(shell, "PATH");
	if (!path_env)
		return (ft_strdup(cmd));
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		if (!full_path)
			return (free_array(paths), NULL);
		full_path = ft_strjoin_free(full_path, cmd);
		if (!full_path)
			return (free_array(paths), NULL);
		if (access(full_path, X_OK) == 0)
			return (free_array(paths), full_path);
		free(full_path);
		i++;
	}
	return (free_array(paths), ft_strdup(cmd));
}

int	execute_cmd(t_shell *shell, t_cmd *cmd, int in_fd, int out_fd)
{
	char	*cmd_path;
	pid_t	pid;
	int		status;

	if (!cmd->args || !cmd->args[0])
		return (0);
	if (is_builtin(cmd->args[0]))
		return (execute_builtin(shell, cmd));
	cmd_path = find_cmd_path(shell, cmd->args[0]);
	if (!cmd_path)
		return (1);
	pid = fork();
	if (pid == 0)
	{
		if (in_fd != STDIN_FILENO)
		{
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
		}
		if (out_fd != STDOUT_FILENO)
		{
			dup2(out_fd, STDOUT_FILENO);
			close(out_fd);
		}
		execve(cmd_path, cmd->args, shell->env_array);
		perror("minishell");
		exit(127);
	}
	free(cmd_path);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
	return (shell->exit_status);
}

int	execute_cmds(t_shell *shell)
{
	t_cmd	*cmd;
	int		pipes[2];
	int		in_fd;
	int		out_fd;

	cmd = shell->cmds;
	in_fd = STDIN_FILENO;
	while (cmd)
	{
		if (cmd->next)
		{
			if (pipe(pipes) == -1)
				return (perror("minishell: pipe"), 1);
			out_fd = pipes[1];
		}
		else
			out_fd = STDOUT_FILENO;
		if (apply_redirections(cmd, &in_fd, &out_fd) == 0)
			execute_cmd(shell, cmd, in_fd, out_fd);
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		if (out_fd != STDOUT_FILENO)
			close(out_fd);
		if (cmd->next)
			in_fd = pipes[0];
		cmd = cmd->next;
	}
	return (shell->exit_status);
}

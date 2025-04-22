/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:18:42 by anonymous         #+#    #+#             */
/*   Updated: 2025/04/22 10:18:42 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_find_cmd_path(char *cmd, char **env_path)
{
	char	*path;
	char	*tmp;
	int		i;

	if (!cmd || !env_path)
		return (NULL);
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	i = 0;
	while (env_path[i])
	{
		tmp = ft_strjoin(env_path[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

static char	**ft_get_env_path(t_env *env_list)
{
	char	*path_str;
	char	**path_arr;

	path_str = ft_getenv(env_list, "PATH");
	if (!path_str)
		return (NULL);
	path_arr = ft_split(path_str, ':');
	return (path_arr);
}

static void	ft_child_process(t_command *cmd, char **env_arr, t_env *env_list)
{
	char	**path;
	char	*cmd_path;

	if (ft_handle_redirections(cmd) != 0)
		exit(1);
	if (ft_is_builtin(cmd->argv[0]))
	{
		exit(ft_execute_builtin(cmd, env_list));
	}
	path = ft_get_env_path(env_list);
	cmd_path = ft_find_cmd_path(cmd->argv[0], path);
	ft_free_arr(path);
	if (!cmd_path)
	{
		ft_error_msg(cmd->argv[0], "command not found", 1);
		exit(127);
	}
	execve(cmd_path, cmd->argv, env_arr);
	ft_error_msg(cmd_path, "execve failed", 1);
	free(cmd_path);
	exit(1);
}

int	ft_execute_pipeline(t_command *cmd_list, t_env *env_list)
{
	t_command	*current;
	char		**env_arr;
	int			status;
	pid_t		pid;
	int			pipefd[2];
	int			prev_pipe;

	current = cmd_list;
	prev_pipe = STDIN_FILENO;
	env_arr = ft_env_to_array(env_list);
	while (current)
	{
		if (current->next)
		{
			if (pipe(pipefd) == -1)
				return (ft_error_msg("pipe", "Failed to create pipe", 1));
		}
		pid = fork();
		if (pid == -1)
			return (ft_error_msg("fork", "Failed to create process", 1));
		if (pid == 0)
		{
			if (prev_pipe != STDIN_FILENO)
			{
				dup2(prev_pipe, STDIN_FILENO);
				close(prev_pipe);
			}
			if (current->next)
			{
				close(pipefd[0]);
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
			}
			ft_child_process(current, env_arr, env_list);
		}
		if (prev_pipe != STDIN_FILENO)
			close(prev_pipe);
		if (current->next)
		{
			close(pipefd[1]);
			prev_pipe = pipefd[0];
		}
		current = current->next;
	}
	ft_free_arr(env_arr);
	while (waitpid(-1, &status, 0) > 0)
		;
	return (WEXITSTATUS(status));
}

int	ft_execute_cmd(t_command *cmd, t_env *env_list)
{
	if (!cmd->argv || !cmd->argv[0])
		return (0);
	if (cmd->next)
		return (ft_execute_pipeline(cmd, env_list));
	if (ft_is_builtin(cmd->argv[0]))
	{
		if (ft_handle_redirections(cmd) != 0)
			return (1);
		return (ft_execute_builtin(cmd, env_list));
	}
	return (ft_execute_pipeline(cmd, env_list));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:00:00 by anonymous         #+#    #+#             */
/*   Updated: 2025/04/22 12:00:00 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	close_pipeline_fds(int *pipe_fds, int count)
{
	int	i;

	i = 0;
	while (i < count * 2)
	{
		close(pipe_fds[i]);
		i++;
	}
}

static void	setup_pipe_redirections(t_cmd *cmd, int *pipe_fds, int cmd_index)
{
	if (cmd_index > 0)
	{
		dup2(pipe_fds[(cmd_index - 1) * 2], STDIN_FILENO);
	}
	if (cmd->next)
	{
		dup2(pipe_fds[cmd_index * 2 + 1], STDOUT_FILENO);
	}
}

static void	execute_piped_cmd(t_cmd *cmd, t_data *data, int *pipe_fds, 
							int cmd_index)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		print_error("fork", "fork failed", NULL);
		return ;
	}
	if (pid == 0)
	{
		setup_pipe_redirections(cmd, pipe_fds, cmd_index);
		close_pipeline_fds(pipe_fds, count_cmds(data->cmd_list));
		setup_redirections(cmd);
		handle_cmd_child(cmd, data);
	}
}

static int	count_cmds(t_cmd *cmd)
{
	int		count;
	t_cmd	*current;

	count = 0;
	current = cmd;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

void	execute_pipeline(t_cmd *cmd, t_data *data)
{
	t_cmd	*current;
	int		*pipe_fds;
	int		cmd_count;
	int		i;
	int		status;

	cmd_count = count_cmds(cmd);
	pipe_fds = malloc(sizeof(int) * (cmd_count - 1) * 2);
	if (!pipe_fds)
		return ;
	i = 0;
	while (i < cmd_count - 1)
	{
		if (pipe(pipe_fds + i * 2) == -1)
		{
			free(pipe_fds);
			return ;
		}
		i++;
	}
	i = 0;
	current = cmd;
	while (current)
	{
		execute_piped_cmd(current, data, pipe_fds, i);
		current = current->next;
		i++;
	}
	close_pipeline_fds(pipe_fds, cmd_count - 1);
	i = 0;
	while (i < cmd_count)
	{
		wait(&status);
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			data->exit_status = 128 + WTERMSIG(status);
		i++;
	}
	free(pipe_fds);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:15:22 by anonymous         #+#    #+#             */
/*   Updated: 2025/04/22 10:15:22 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_redirect_in(t_redirection *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd < 0)
		return (ft_error_msg(redir->file, "No such file or directory", 1));
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		return (ft_error_msg("dup2", "Failed to redirect input", 1));
	}
	close(fd);
	return (0);
}

static int	handle_redirect_out(t_redirection *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (ft_error_msg(redir->file, "Permission denied", 1));
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (ft_error_msg("dup2", "Failed to redirect output", 1));
	}
	close(fd);
	return (0);
}

static int	handle_redirect_append(t_redirection *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (ft_error_msg(redir->file, "Permission denied", 1));
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (ft_error_msg("dup2", "Failed to redirect output", 1));
	}
	close(fd);
	return (0);
}

static int	handle_heredoc(t_redirection *redir)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
		return (ft_error_msg("pipe", "Failed to create pipe", 1));
	while (1)
	{
		ft_putstr_fd("> ", STDERR_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, redir->file, ft_strlen(redir->file)) == 0
			&& line[ft_strlen(redir->file)] == '\n')
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, pipe_fd[1]);
		free(line);
	}
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		return (ft_error_msg("dup2", "Failed to redirect input", 1));
	close(pipe_fd[0]);
	return (0);
}

int	ft_handle_redirections(t_command *cmd)
{
	t_redirection	*redir;
	int				ret;

	ret = 0;
	redir = cmd->redirections;
	while (redir && ret == 0)
	{
		if (redir->type == REDIR_IN)
			ret = handle_redirect_in(redir);
		else if (redir->type == REDIR_OUT)
			ret = handle_redirect_out(redir);
		else if (redir->type == REDIR_APPEND)
			ret = handle_redirect_append(redir);
		else if (redir->type == REDIR_HEREDOC)
			ret = handle_heredoc(redir);
		redir = redir->next;
	}
	return (ret);
}

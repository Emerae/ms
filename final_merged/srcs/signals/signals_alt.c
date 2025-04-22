/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:22:15 by anonymous         #+#    #+#             */
/*   Updated: 2025/04/22 10:22:15 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', STDERR_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_status = 130;
	}
}

static void	ft_signal_handler_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', STDERR_FILENO);
		close(STDIN_FILENO);
		g_status = 130;
	}
}

void	ft_setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = ft_signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_setup_signals_heredoc(void)
{
	struct sigaction	sa;

	sa.sa_handler = ft_signal_handler_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_setup_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

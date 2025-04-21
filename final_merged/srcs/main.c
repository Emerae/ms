/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:00:00 by student           #+#    #+#             */
/*   Updated: 2023/09/22 12:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_status;

void	handle_input(t_shell *shell, char *input)
{
	if (!input)
		exit_shell(shell, 0);
	if (input[0] != '\0')
	{
		add_history(input);
		shell->tokens = tokenize_input(input);
		if (shell->tokens)
		{
			shell->cmds = parse_tokens(shell);
			if (shell->cmds)
				execute_cmds(shell);
			free_cmds(shell->cmds);
			shell->cmds = NULL;
		}
		free_tokens(shell->tokens);
		shell->tokens = NULL;
	}
	free(input);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*input;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("Error: No arguments needed\n", 2);
		return (1);
	}
	init_shell(&shell, envp);
	setup_signals();
	while (1)
	{
		shell.in_cmd = 0;
		input = readline("minishell$ ");
		shell.in_cmd = 1;
		handle_input(&shell, input);
	}
	return (0);
}

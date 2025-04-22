/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:00:00 by anonymous         #+#    #+#             */
/*   Updated: 2025/04/22 12:00:00 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_data	*init_data(char **envp)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->env = init_env(envp);
	data->cmd_list = NULL;
	data->input = NULL;
	data->exit = 0;
	data->exit_status = 0;  /* Initialize exit status to 0 */
	return (data);
}

void	init_shell(t_data *data)
{
	setup_signals();
	while (!data->exit)
	{
		data->input = readline("minishell$ ");
		if (!data->input)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		}
		if (data->input[0] != '\0')
		{
			add_history(data->input);
			if (parse_input(data) == 0)
				execute_cmd(data->cmd_list, data);
			free_cmds(data->cmd_list);
			data->cmd_list = NULL;
		}
		free(data->input);
		data->input = NULL;
		if (g_sig_status)
		{
			if (g_sig_status == 1)  /* SIGINT */
				data->exit_status = 130;
			else if (g_sig_status == 2)  /* SIGQUIT */
				data->exit_status = 131;
			g_sig_status = 0;
		}
	}
}

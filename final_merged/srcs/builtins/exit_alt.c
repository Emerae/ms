/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:00:00 by anonymous         #+#    #+#             */
/*   Updated: 2025/04/22 12:00:00 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(char **args, t_data *data)
{
	long	exit_code;

	ft_putendl_fd("exit", STDERR_FILENO);
	if (!args[1])
		exit_shell(data, g_exit_status);
	if (!is_numeric(args[1]))
	{
		print_error("exit", "numeric argument required", args[1]);
		exit_shell(data, 255);
	}
	exit_code = ft_atoi(args[1]);
	if (args[2])
	{
		print_error("exit", "too many arguments", NULL);
		return (1);
	}
	exit_shell(data, exit_code & 255);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:00:00 by anonymous         #+#    #+#             */
/*   Updated: 2025/04/22 12:00:00 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_pwd(void)
{
	char	cwd[4096];

	if (!getcwd(cwd, 4096))
	{
		print_error("pwd", strerror(errno), NULL);
		return (1);
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	return (0);
}

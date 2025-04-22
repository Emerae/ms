/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:00:00 by anonymous         #+#    #+#             */
/*   Updated: 2025/04/22 12:00:00 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_var_name(char *str, int *i)
{
	int		start;
	char	*var_name;

	start = *i;
	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	if (!ft_isalpha(str[*i]) && str[*i] != '_')
		return (ft_strdup(""));
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var_name = ft_substr(str, start + 1, *i - start - 1);
	return (var_name);
}

static char	*get_var_value(char *var_name, t_data *data)
{
	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(data->exit_status));
	return (ft_strdup(get_env_value(data->env, var_name) ? 
				get_env_value(data->env, var_name) : ""));
}

static char	*expand_string(char *str, t_data *data)
{
	int		i;
	int		in_quotes;
	char	*result;
	char	*var_name;
	char	*var_value;
	char	*temp;

	if (!str)
		return (NULL);
	result = ft_strdup("");
	i = 0;
	in_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			if (!in_quotes)
				in_quotes = 1;
			else if (in_quotes == 1)
				in_quotes = 0;
		}
		else if (str[i] == '\"')
		{
			if (!in_quotes)
				in_quotes = 2;
			else if (in_quotes == 2)
				in_quotes = 0;
		}
		else if (str[i] == '$' && (in_quotes != 1))
		{
			var_name = get_var_name(str, &i);
			var_value = get_var_value(var_name, data);
			temp = ft_strjoin(result, var_value);
			free(result);
			free(var_name);
			free(var_value);
			result = temp;
			continue ;
		}
		temp = ft_charjoin(result, str[i]);
		free(result);
		result = temp;
		i++;
	}
	return (result);
}

void	expand_tokens(t_token *tokens, t_data *data)
{
	char	*expanded;

	while (tokens)
	{
		if (tokens->type != HEREDOC_DELIM)
		{
			expanded = expand_string(tokens->value, data);
			free(tokens->value);
			tokens->value = expanded;
		}
		tokens = tokens->next;
	}
}

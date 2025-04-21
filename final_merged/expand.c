/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:00:00 by student           #+#    #+#             */
/*   Updated: 2023/09/22 12:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_name(char *str, int *i)
{
	int		start;
	int		len;
	char	*var_name;

	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	len = *i - start;
	var_name = (char *)malloc(sizeof(char) * (len + 1));
	if (!var_name)
		return (NULL);
	ft_strncpy(var_name, str + start, len);
	var_name[len] = '\0';
	return (var_name);
}

char	*expand_var(t_shell *shell, char *str, int *i)
{
	char	*var_name;
	char	*var_value;
	char	*result;

	if (str[*i] == '$')
	{
		(*i)++;
		if (str[*i] == '?')
		{
			(*i)++;
			return (ft_itoa(shell->exit_status));
		}
		else if (ft_isalnum(str[*i]) || str[*i] == '_')
		{
			var_name = get_var_name(str, i);
			if (!var_name)
				return (NULL);
			var_value = get_env_value(shell, var_name);
			free(var_name);
			if (var_value)
				result = ft_strdup(var_value);
			else
				result = ft_strdup("");
			return (result);
		}
		else
			return (ft_strdup("$"));
	}
	return (NULL);
}

char	*handle_str_inside_quotes(t_shell *shell, char *str, int *i, char quote)
{
	int		start;
	int		len;
	char	*result;
	char	*temp;
	char	*var_expansion;

	start = *i;
	while (str[*i] && str[*i] != quote)
	{
		if (quote == '\"' && str[*i] == '$')
		{
			len = *i - start;
			result = (char *)malloc(sizeof(char) * (len + 1));
			if (!result)
				return (NULL);
			ft_strncpy(result, str + start, len);
			result[len] = '\0';
			var_expansion = expand_var(shell, str, i);
			if (!var_expansion)
				return (free(result), NULL);
			temp = ft_strjoin(result, var_expansion);
			free(result);
			free(var_expansion);
			result = temp;
			start = *i;
		}
		else
			(*i)++;
	}
	if (*i > start)
	{
		len = *i - start;
		temp = (char *)malloc(sizeof(char) * (len + 1));
		if (!temp)
			return (NULL);
		ft_strncpy(temp, str + start, len);
		temp[len] = '\0';
		if (result)
		{
			var_expansion = ft_strjoin(result, temp);
			free(result);
			free(temp);
			result = var_expansion;
		}
		else
			result = temp;
	}
	return (result);
}

char	*expand_vars(t_shell *shell, char *str)
{
	int		i;
	int		start;
	char	*result;
	char	*temp;
	char	*var_expansion;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (str[i])
	{
		start = i;
		if (str[i] == '\'')
		{
			i++;
			temp = handle_str_inside_quotes(shell, str, &i, '\'');
			if (!temp)
				return (free(result), NULL);
			var_expansion = ft_strjoin(result, temp);
			free(result);
			free(temp);
			result = var_expansion;
			if (str[i] == '\'')
				i++;
		}
		else if (str[i] == '\"')
		{
			i++;
			temp = handle_str_inside_quotes(shell, str, &i, '\"');
			if (!temp)
				return (free(result), NULL);
			var_expansion = ft_strjoin(result, temp);
			free(result);
			free(temp);
			result = var_expansion;
			if (str[i] == '\"')
				i++;
		}
		else if (str[i] == '$')
		{
			var_expansion = expand_var(shell, str, &i);
			if (!var_expansion)
				return (free(result), NULL);
			temp = ft_strjoin(result, var_expansion);
			free(result);
			free(var_expansion);
			result = temp;
		}
		else
		{
			while (str[i] && str[i] != '\'' && str[i] != '\"' && str[i] != '$')
				i++;
			temp = (char *)malloc(sizeof(char) * (i - start + 1));
			if (!temp)
				return (free(result), NULL);
			ft_strncpy(temp, str + start, i - start);
			temp[i - start] = '\0';
			var_expansion = ft_strjoin(result, temp);
			free(result);
			free(temp);
			result = var_expansion;
		}
	}
	return (remove_quotes(result));
}

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*result;
	char	quote;

	result = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				result[j++] = str[i++];
			if (str[i])
				i++;
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	free(str);
	return (result);
}

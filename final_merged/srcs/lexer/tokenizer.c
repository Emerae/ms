/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:00:00 by student           #+#    #+#             */
/*   Updated: 2023/09/22 12:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *content, t_token_type type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->content = ft_strdup(content);
	if (!new_token->content)
	{
		free(new_token);
		return (NULL);
	}
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

void	add_token(t_token **tokens, t_token *new_token)
{
	t_token	*current;

	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	current = *tokens;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

t_token_type	identify_token_type(char *str)
{
	if (ft_strcmp(str, "|") == 0)
		return (T_PIPE);
	else if (ft_strcmp(str, "<") == 0)
		return (T_REDIR_IN);
	else if (ft_strcmp(str, ">") == 0)
		return (T_REDIR_OUT);
	else if (ft_strcmp(str, ">>") == 0)
		return (T_APPEND);
	else if (ft_strcmp(str, "<<") == 0)
		return (T_HEREDOC);
	return (T_WORD);
}

int	handle_quotes(char *input, int *i, char quote)
{
	(*i)++;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (!input[*i])
		return (0);
	return (1);
}

char	*extract_token(char *input, int *i)
{
	int		start;
	int		len;
	char	*token;

	while (input[*i] && ft_isspace(input[*i]))
		(*i)++;
	start = *i;
	if (input[*i] == '|')
		(*i)++;
	else if (input[*i] == '<' || input[*i] == '>')
	{
		(*i)++;
		if (input[*i] == input[*i - 1])
			(*i)++;
	}
	else
	{
		while (input[*i] && !ft_isspace(input[*i]) && input[*i] != '|'
			&& input[*i] != '<' && input[*i] != '>')
		{
			if (input[*i] == '\'' || input[*i] == '\"')
				if (!handle_quotes(input, i, input[*i]))
					return (NULL);
			(*i)++;
		}
	}
	len = *i - start;
	token = malloc(sizeof(char) * (len + 1));
	if (!token)
		return (NULL);
	ft_strncpy(token, input + start, len);
	token[len] = '\0';
	return (token);
}

t_token	*tokenize_input(char *input)
{
	t_token	*tokens;
	int		i;
	char	*token_str;
	t_token	*new_token;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		token_str = extract_token(input, &i);
		if (!token_str)
			return (free_tokens(tokens), NULL);
		new_token = create_token(token_str, identify_token_type(token_str));
		if (!new_token)
			return (free(token_str), free_tokens(tokens), NULL);
		add_token(&tokens, new_token);
		free(token_str);
	}
	return (tokens);
}

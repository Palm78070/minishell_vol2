/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 21:52:09 by rthammat          #+#    #+#             */
/*   Updated: 2023/01/27 22:50:26 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_error_ok(char *s, char *quote)
{
	int	i;
	int	is_ok;

	i = 0;
	is_ok = 1;
	while (s[i])
	{
		if (s[i] && (s[i] == '\'' || s[i] == '"'))
		{
			is_ok = 0;
			*quote = s[i++];
			while (s[i] && s[i] != *quote)
				++i;
			if (s[i] && s[i] == *quote)
				is_ok = 1;
			++i;
		}
		else
			++i;
	}
	if (is_ok == 0)
		return (0);
	return (1);
}

int	pipe_error_ok(char *s)
{
	int	i;

	i = ft_strlen(s) - 1;
	while (i >= 0 && ft_isspace(s[i]) && s[i] != '|')
		--i;
	if (s[i] && s[i] == '|')
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] && s[i] == '|')
		{
			while (s[++i] && ft_isspace(s[i]) && s[i] != '|')
				continue ;
			if (s[i] && s[i] == '|')
				return (0);
		}
		else
			++i;
	}
	return (1);
}

int	arrow_error_ok(char *s, char *c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] && (s[i] == '<' || s[i] == '>'))
		{
			*c = s[i];
			while (s[++i] && ft_isspace(s[i]) && s[i] != *c)
				continue ;
			if (s[i] && s[i] == *c)
				return (0);
		}
		else
			++i;
	}
	i = ft_strlen(s) - 1;
	while (i >= 0 && ft_isspace(s[i]) && s[i] != '<' && s[i] != '>')
		--i;
	if (s[i] && (s[i] == '<' || s[i] == '>'))
	{
		*c = s[i];
		return (0);
	}
	return (1);
}

int	check_error_ok(char *s)
{
	char	c;

	c = 0;
	if (!quote_error_ok(s, &c))
	{
		printf("syntax error: token have no closed quote %c\n", c);
		return (0);
	}
	if (!pipe_error_ok(s))
	{
		printf("syntax error near unexpected token '|'\n");
		return (0);
	}
	if (!arrow_error_ok(s, &c))
	{
		printf("syntax error near unexpected token '%c'\n", c);
		return (0);
	}
	return (1);
}

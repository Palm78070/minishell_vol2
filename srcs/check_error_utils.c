/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 21:52:09 by rthammat          #+#    #+#             */
/*   Updated: 2023/01/30 23:21:22 by rthammat         ###   ########.fr       */
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
		printf("syntax error: token have no closed quote %c\n", *quote);
	return (is_ok);
}

int	pipe_error_ok(char *s)
{
	int	i;
	int	is_ok;

	is_ok = 1;
	i = ft_strlen(s) - 1;
	while (i >= 0 && ft_isspace(s[i]) && s[i] != '|')
		--i;
	if (s[i] && s[i] == '|')
		is_ok = 0;
	i = 0;
	while (s[i] && is_ok)
	{
		if (s[i] && (s[i] == '\'' || s[i] == '"'))
			is_ok = s[i];
		while (s[i] && s[i] != is_ok + '0')
			++i;
		if (s[i] && s[i] == '|')
		{
			while (s[++i] && ft_isspace(s[i]) && s[i] != '|')
				continue ;
			if (s[i] && s[i] == '|')
				is_ok = 0;
		}
		else
			++i;
	}
	if (!is_ok)
		printf("syntax error near unexpected token '|'\n");
	return (is_ok);
}

int	double_arrow_error_ok(char *s, char c, int i)
{
	int	count;

	count = 0;
	while (s[i] && ft_isspace(s[i]))
		++i;
	if (s[i] == '\0')
		printf("syntax error near unexpected token 'newline'\n");
	if (s[i] && (s[i] == '<' || s[i] == '>'))
		c = s[i];
	while (s[i] && s[i++] == c)
		++count;
	if (count > 0)
	{
		i = 0;
		printf("syntax error near unexpected token '");
		while (i < count && i++ <= 2)
			printf("%c", c);
		printf("'\n");
	}
	if (s[i] == '\0' || count > 0)
		return (-2);
	return (1);
}

int	is_not_file(char *s, int i)
{
	if (s[i + 1] && s[i] == '>' && s[i + 1] == '>')
	{
		if (is_blank_quote(&s[i + 2]))
		{
			printf("No such file or directory\n");
			return (1);
		}
	}
	else if (s[i] == '<' || s[i] == '>')
	{
		if (is_blank_quote(&s[i + 1]))
		{
			printf("No such file or directory\n");
			return (1);
		}
	}
	return (0);
}

int	arrow_error_ok(char *s, char *c, int *i)
{
	while (s[*i])
	{
		if (s[*i] && (s[*i] == '<' || s[*i] == '>'))
		{
			*c = s[*i];
			if (is_not_file(s, *i))
				return (-2);
			if (s[*i + 1] && s[*i] == *c && s[*i + 1] == *c)
				return (double_arrow_error_ok(s, *c, *i + 2));
			while (s[++(*i)] && ft_isspace(s[*i]) && s[*i] != '<' && s[*i] != '>')
				continue ;
			if (s[*i] && (s[*i] == '<' || s[*i] == '>'))
			{
				*c = s[*i];
				return (-1);
			}
		}
		else
			++(*i);
	}
	*i = ft_strlen(s) - 1;
	while (*i >= 0 && ft_isspace(s[*i]) && s[*i] != '<' && s[*i] != '>')
		--(*i);
	return (!(s[*i] && (s[*i] == '<' || s[*i] == '>')));
}
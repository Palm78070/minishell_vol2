/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 00:18:47 by rthammat          #+#    #+#             */
/*   Updated: 2023/02/07 22:46:22 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_head(char *s, int delim_indx)
{
	int		i;
	int		len;
	char	*res;

	i = -1;
	len = ft_strlen(s) - delim_indx;
	if (len <= 0)
	{
		free(s);
		return (NULL);
	}
	res = (char *)malloc(sizeof(char) * len);
	if (!res)
		return (NULL);
	while (s[++delim_indx])
		res[++i] = s[delim_indx];
	res[++i] = '\0';
	free(s);
	return (res);
}

static int	is_double_arrow(char *s, int i)
{
	if (s[i + 1])
		return (s[i + 1] == '<' || s[i + 1] == '>');
	return (0);
}

int	check_state(char *s, int i)
{
	if (s == NULL || !s[i])
		return (0);
	if (ft_isspace(s[i]))
		return (SP);
	else if ((s[i] == '<' || s[i] == '>') && is_double_arrow(s, i))
	{
		if (s[i] == '<' && s[i + 1] == '<')
			return (HEREDOC);
		if (s[i] == '>' && s[i + 1] == '>')
			return (APPEND);
	}
	else if (s[i] == '<')
		return (REDIRECT_I);
	else if (s[i] == '>')
		return (REDIRECT_O);
	else if (s[i] == '\'')
		return (S_QUOTE);
	else if (s[i] == '\"')
		return (D_QUOTE);
	else if (s[i] == '|' && s[i + 1] && s[i + 1] == '|')
		return (OR_IF);
	else if (s[i] == '|')
		return (PIPE);
	else if (s[i] == '&' && s[i + 1] && s[i + 1] == '&')
		return (AND_IF);
	return (0);
}

t_lst	*insert_str(t_msh *ms, t_lst *lst, int i)
{
	char	*str_tmp;

	str_tmp = NULL;
	str_tmp = ft_substr(ms->line, 0, i);
	lst = insert_end(lst, str_tmp);
	free(str_tmp);
	return (lst);
}

char	*ft_insert_char(char *old, char c)
{
	char	*res;
	int	len;
	int	i;

	i = 0;
	if (old == NULL)
		len = 2;
	else
		len = ft_strlen(old) + 2;
	res = (char *)malloc(sizeof(char) * len);
	if (!res)
		return (NULL);
	while (old && old[i])
	{
		res[i] = old[i];
		++i;
	}
	res[i++] = c;
	res[i] = '\0';
	if (old)
		free(old);
	return (res);
}

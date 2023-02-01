/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 21:06:33 by rthammat          #+#    #+#             */
/*   Updated: 2023/02/01 14:22:42 by rath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_blank_quote(char *s)
{
	int	i;

	i = 0;
	if (s == NULL || s[i] == '\0')
		return (0);
	while (s[i])
	{
		if (!is_quote(s[i++]))
			return (0);
	}
	return (1);
}

int	still_have_quote(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
	{
		if (s[i++] == '$')
			return (0);
	}
	i = 0;
	while (s[i])
	{
		if (is_quote(s[i++]))
			return (1);
	}
	return (0);
}

t_lst	*ft_lexer(t_msh *ms)
{
	t_lst	*lst;
	t_lst	*ptr;

	lst = ft_token(ms);
	ptr = lst;
	while (ptr)
	{
		if (ptr->data && is_blank_quote(ptr->data))
		{
			ft_remove_if_addr(&lst, ptr->data);
			ptr = lst;
		}
		else
			ptr = ptr->next;
	}
	ptr = lst;
	while (ptr)
	{
		while (still_have_quote(ptr->data))
			ptr->data = remove_quote(ptr->data);
		ptr = ptr->next;
	}
	return (lst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:16:50 by rthammat          #+#    #+#             */
/*   Updated: 2023/01/30 22:40:07 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_simple_cmd(t_msh *ms, t_lst *lst)
{
	int	count_pipe;

	count_pipe = 0;
	while (lst)
	{
		ms->state = check_state(lst->data, 0);
		if (ms->state == PIPE)
			++count_pipe;
		lst = lst->next;
	}
	return (count_pipe + 1);
}

int	count_arg_size(t_msh *ms, t_lst *lst)
{
	int	count_arg;

	count_arg = 0;
	while (lst)
	{
		ms->state = check_state(lst->data, 0);
		if (ms->state == PIPE)
			break ;
		++count_arg;
		lst = lst->next;
	}
	return (count_arg);
}
/*
char	*insert_words(int arg_size)
{
	char	*res;
	int	i;

	res = (char *)malloc(sizeof(char) * arg_size);
	i = 0;
	if (!res)
		return (NULL);
	while (i < arg_size)
	{
		++i;
	}
}*/

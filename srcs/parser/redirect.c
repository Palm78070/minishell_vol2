/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:06:09 by rthammat          #+#    #+#             */
/*   Updated: 2023/03/01 11:51:18 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_redirect(t_msh *ms)
{
	int	i;

	i = 0;
	while (i < ms->parse.cmd_size)
	{
		ms->redout[i].fd_out = -1;
		ms->redout[i].filename = NULL;
		ms->redout[i].append = 0;
		ms->redout[i].output = 0;
		ms->redin[i].fd_in = -1;
		ms->redin[i].filename = NULL;
		ms->redin[i].output = 0;
		ms->heredoc[i].delim = NULL;
		ms->heredoc[i].output = 0;
		ms->heredoc[i].pipe[0] = -1;
		ms->heredoc[i].pipe[1] = -1;
		++i;
	}
}

int	is_redirect(t_msh *ms, t_lst *lst)
{
	if (!list_ok(&lst))
		return (0);
	ms->state = check_state(lst->data, 0);
	if (ms->state == REDIRECT_I || ms->state == REDIRECT_O \
		|| ms->state == HEREDOC || ms->state == APPEND)
		return (ms->state);
	return (0);
}

int	is_all_space(char *s)
{
	int	i;

	i = 0;
	if (s == NULL || *s == '\0')
		return (0);
	while (s[i])
	{
		if (!ft_isspace(s[i++]))
			return (0);
	}
	return (1);
}

void	handle_redirect(t_msh *ms, t_lst **lst, int i)
{
	int	flag;

	flag = is_redirect(ms, *lst);
	while (flag)
	{
		remove_head_node(lst);
		while (list_ok(lst) && is_all_space((*lst)->data))
			remove_head_node(lst);
		if (flag == REDIRECT_O || flag == APPEND)
		{
			if (flag == APPEND)
				ms->redout[i].append = 1;
			parse_red_out(ms, lst, i);
		}
		else if (flag == REDIRECT_I)
			parse_red_in(ms, lst, i);
		else if (flag == HEREDOC)
			parse_heredoc(ms, lst, i);
		remove_head_node(lst);
		flag = is_redirect(ms, *lst);
	}
}

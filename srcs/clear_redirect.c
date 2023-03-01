/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 17:27:25 by rthammat          #+#    #+#             */
/*   Updated: 2023/02/26 00:42:02 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_filename(char *s)
{
	if (s != NULL)
	{
		free(s);
		s = NULL;
	}
}

void	free_simple_redirect(t_msh *ms, int i)
{
	if (ms->redout)
	{
		if (ms->redout[i].filename)
			free_list(ms->redout[i].filename);
		if (ms->redout[i].fd_out != -1)
			close(ms->redout[i].fd_out);
	}
	if (ms->redin)
	{
		if (ms->redin[i].filename)
			free_list(ms->redin[i].filename);
		if (ms->redin[i].fd_in != -1)
			close(ms->redin[i].fd_in);
	}
	if (ms->heredoc && ms->heredoc[i].delim)
		free_list(ms->heredoc[i].delim);
}

void	free_redirect(t_msh *ms)
{
	int	i;

	i = 0;
	while (i < ms->parse.cmd_size)
		free_simple_redirect(ms, i++);
	free(ms->redout);
	ms->redout = NULL;
	free(ms->redin);
	ms->redin = NULL;
	free(ms->heredoc);
	ms->heredoc = NULL;
}

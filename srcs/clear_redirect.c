/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 17:27:25 by rthammat          #+#    #+#             */
/*   Updated: 2023/02/19 00:05:08 by rthammat         ###   ########.fr       */
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
	if (ms->redout[i].filename)
		free_list(ms->redout[i].filename);
	if (ms->redin[i].filename)
		free_list(ms->redin[i].filename);
	if (ms->append[i].filename)
		free_list(ms->append[i].filename);
	if (ms->heredoc[i].delim)
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
	free(ms->append);
	ms->append = NULL;
	free(ms->heredoc);
	ms->heredoc = NULL;
}

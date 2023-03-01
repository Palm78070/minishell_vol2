/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:10:02 by rthammat          #+#    #+#             */
/*   Updated: 2023/03/01 11:59:30 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_flag_output(t_msh *ms, int i)
{
	if (ms->redout[i].output == 1)
		ms->redout[i].output = 0;
	if (ms->redin[i].output == 1)
		ms->redin[i].output = 0;
	if (ms->heredoc[i].output == 1)
		ms->heredoc[i].output = 0;
}

int	is_env_var(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '$')
		++i;
	if (s[i] == '$')
		return (1);
	return (0);
}

void	parse_red_out(t_msh *ms, t_lst **lst, int i)
{
	if (!list_ok(lst))
		return ;
	clear_flag_output(ms, i);
	ms->redout[i].output = 1;
	ms->redout[i].filename = insert_end(ms->redout[i].filename, (*lst)->data);
	/////////////////////////////////////////////////////////////////////////
	printf("filename out is\n");
	print_list(ms->redout[i].filename);
	/////////////////////////////////////////////////////////////////////////
}

void	parse_red_in(t_msh *ms, t_lst **lst, int i)
{
	if (!list_ok(lst))
		return ;
	clear_flag_output(ms, i);
	ms->redin[i].output = 1;
	ms->redin[i].filename = insert_end(ms->redin[i].filename, (*lst)->data);
	/////////////////////////////////////////////////////////////////////////
	printf("filename redin is\n");
	print_list(ms->redin[i].filename);
	/////////////////////////////////////////////////////////////////////////
}

void	parse_heredoc(t_msh *ms, t_lst **lst, int i)
{
	if (!list_ok(lst))
		return ;
	clear_flag_output(ms, i);
	ms->heredoc[i].output = 1;
	ms->heredoc[i].delim = insert_end(ms->heredoc[i].delim, (*lst)->data);
	/////////////////////////////////////////////////////////////////////////
	printf("heredoc delim is\n");
	print_list(ms->heredoc[i].delim);
	/////////////////////////////////////////////////////////////////////////
}

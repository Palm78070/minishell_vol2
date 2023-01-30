/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 00:44:00 by rthammat          #+#    #+#             */
/*   Updated: 2023/01/30 18:16:58 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*token_space(t_msh *ms, t_lst *lst, int *index)
{
	int	i;

	i = *index;
	if (i > 0)
		lst = insert_str(ms, lst, i);
	lst = insert_end(lst, " ");
	while (ms->line[i] && ft_isspace(ms->line[i]))
		++i;
	ms->line = trim_head(ms->line, --i);
	*index = 0;
	return (lst);
}

t_lst	*token_pipe(t_msh *ms, t_lst *lst, int *index)
{
	int	i;

	i = *index;
	if (i > 0)
		lst = insert_str(ms, lst, i);
	lst = insert_end(lst, "|");
	ms->line = trim_head(ms->line, i);
	*index = 0;
	return (lst);
}

t_lst	*token_redirect(t_msh *ms, t_lst *lst, int *index)
{
	int	i;

	i = *index;
	if (i > 0)
		lst = insert_str(ms, lst, i);
	if (ms->state == REDIRECT_I)
		lst = insert_end(lst, "<");
	else if (ms->state == REDIRECT_O)
		lst = insert_end(lst, ">");
	ms->line = trim_head(ms->line, i);
	*index = 0;
	return (lst);
}

t_lst	*token_double_sign(t_msh *ms, t_lst *lst, int *index)
{
	char	*str_tmp;
	int		i;

	str_tmp = NULL;
	i = *index;
	if (i > 0)
	{
		lst = insert_str(ms, lst, i);
		ms->line = trim_head(ms->line, i - 1);
	}
	i = 2;
	str_tmp = ft_substr(ms->line, 0, i);
	lst = insert_end(lst, str_tmp);
	ms->line = trim_head(ms->line, i - 1);
	free(str_tmp);
	*index = 0;
	return (lst);
}

t_lst	*ft_token(t_msh *ms)
{
	int		i;
	t_lst	*lst;

	i = 0;
	lst = NULL;
	while (ms->line && ms->line[i])
	{
		ms->state = check_state(ms->line, i);
		check_quote(ms->line, &i);
		if (ms->state == SP)
			lst = token_space(ms, lst, &i);
		else if (ms->state == PIPE)
			lst = token_pipe(ms, lst, &i);
		else if (ms->state == REDIRECT_I || ms->state == REDIRECT_O)
			lst = token_redirect(ms, lst, &i);
		else if (ms->state == HEREDOC || ms->state == APPEND
			|| ms->state == AND_IF || ms->state == OR_IF)
			lst = token_double_sign(ms, lst, &i);
		else
			++i;
	}
	if (ms->line && ms->line[0])
		lst = insert_str(ms, lst, i);
	return (lst);
}

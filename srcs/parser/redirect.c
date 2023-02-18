/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:06:09 by rthammat          #+#    #+#             */
/*   Updated: 2023/02/18 23:49:55 by rthammat         ###   ########.fr       */
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
		ms->redin[i].filename = NULL;
		ms->append[i].fd_append = -1;
		ms->append[i].filename = NULL;
		ms->heredoc[i].delim = NULL;
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

/*char	*ft_filename(t_lst **lst)
{
	t_lst	*ptr;

	ptr = *lst;
	while (ptr && is_all_space(ptr->data))
	{
		printf("ptr->data %s\n", ptr->data);
		ptr = ptr->next;
	}
	if (ptr)
	{
		printf("filename is %s\n", ptr->data);
		return (ptr->data);
	}
	return (NULL);
}*/

void	handle_redirect(t_msh *ms, t_lst **lst, int i)
{
	int	flag;

	flag = is_redirect(ms, *lst);
	while (flag)
	{
		remove_head_node(lst);
		while (list_ok(lst) && is_all_space((*lst)->data))
			remove_head_node(lst);
		if (flag == REDIRECT_O)
			parse_red_out(ms, lst, i);
		else if (flag == REDIRECT_I)
			parse_red_in(ms, lst, i);
		else if (flag == HEREDOC)
			parse_heredoc(ms, lst, i);
		else if (flag == APPEND)
			parse_append(ms, lst, i);
		remove_head_node(lst);
		flag = is_redirect(ms, *lst);
	}
}

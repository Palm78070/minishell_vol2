/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:16:50 by rthammat          #+#    #+#             */
/*   Updated: 2023/01/31 09:08:46 by rthammat         ###   ########.fr       */
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

t_cmd	*insert_args(t_msh *ms, t_lst **lst, int arg_size)
{
	t_cmd	*res;
	int	i;

	res = (t_cmd *)malloc(sizeof(t_cmd) * (arg_size + 1));
	i = 0;
	if (!res)
		return (NULL);
	res[arg_size].arg = NULL;
	while (i < arg_size)
	{
		res[i].arg = ft_strdup((*lst)->data);
		if (!res)
			return (NULL);
		remove_head_node(lst);
		++i;
	}
	if (lst && *lst && (*lst)->data)
		ms->state = check_state((*lst)->data, 0);
	if (ms->state == PIPE && lst)
		remove_head_node(lst);
	return (res);
}

void	print_arg(t_cmd **s_cmd, int cmd_size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < cmd_size)
	{
		j = 0;
		while (s_cmd[i][j].arg != NULL)
		{
			printf("arg %s\n", s_cmd[i][j].arg);
			++j;
		}
		++i;
	}
}
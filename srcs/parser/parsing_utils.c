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
		if (is_redirect(ms, lst))
			lst = lst->next->next;
		else
		{
			++count_arg;
			lst = lst->next;
		}
	}
	return (count_arg);
}

t_cmd	*insert_args(t_msh *ms, t_lst **lst)
{
	t_cmd	*res;
	int	arg_size;
	int	i;

	arg_size = ms->parse.arg_size;;
	res = (t_cmd *)malloc(sizeof(t_cmd) * (arg_size + 1));
	i = 0;
	if (!res)
		return (NULL);
	res[arg_size].arg = NULL;
	while (list_ok(lst))
	{
		handle_redirect(ms, lst);
		if (!list_ok(lst) || check_state((*lst)->data, 0) == PIPE)
			break ;
		res[i++].arg = ft_strdup((*lst)->data);
		if (!res)
			return (NULL);
		remove_head_node(lst);
	}
	if (list_ok(lst) && check_state((*lst)->data, 0) == PIPE)
		remove_head_node(lst);
	return (res);
}

void	print_arg(t_msh *ms)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < ms->parse.cmd_size)
	{
		j = 0;
		while (ms->s_cmd[i][j].arg != NULL)
		{
			printf("arg[%i] %s\n", i, ms->s_cmd[i][j].arg);
			++j;
		}
		++i;
	}
}

void	create_command_tab(t_msh *ms, t_lst **lst)
{
	int	i;

	i = 0;
	init_redirect(ms);
	ms->parse.cmd_size = count_simple_cmd(ms, *lst);
	printf("cmd_size %i\n", ms->parse.cmd_size);
	ms->s_cmd = (t_cmd **)malloc(sizeof(t_cmd *) * ms->parse.cmd_size);
	while (i < ms->parse.cmd_size)
	{
		printf("i %i\n", i);
		ms->parse.arg_size = count_arg_size(ms, *lst);
		printf("arg_size %i\n", ms->parse.arg_size);
		ms->s_cmd[i] = insert_args(ms, lst);
		++i;
	}
}
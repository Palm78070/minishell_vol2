/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:16:50 by rthammat          #+#    #+#             */
/*   Updated: 2023/02/28 08:26:14 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_arg_for_tab(t_msh *ms, t_lst *lst)
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
	ms->parse.cmd_size = count_pipe + 1;
}

int	count_arg_size(t_msh *ms, t_lst *lst)
{
	int	count_arg;

	count_arg = 0;
	while (list_ok(&lst))
	{
		ms->state = check_state(lst->data, 0);
		if (ms->state == PIPE)
			break ;
		if (list_ok(&lst) && is_redirect(ms, lst))
		{
			lst = lst->next;
			while (list_ok(&lst) && is_all_space(lst->data))
				lst = lst->next;
			if (list_ok(&lst))
				lst = lst->next;
		}
		else
		{
			++count_arg;
			lst = lst->next;
		}
	}
	return (count_arg);
}

char	**insert_args(t_msh *ms, t_lst **lst, int i)
{
	char	**res;
	int		arg_size;
	int		j;

	arg_size = ms->parse.arg_size;
	res = (char **)malloc(sizeof(char *) * (arg_size + 1));
	j = 0;
	if (!res)
		return (NULL);
	res[arg_size] = NULL;
	while (list_ok(lst))
	{
		handle_redirect(ms, lst, i);
		if (!list_ok(lst) || check_state((*lst)->data, 0) == PIPE)
			break ;
		res[j++] = ft_strdup((*lst)->data);
		if (!res)
			return (NULL);
		remove_head_node(lst);
	}
	res[j] = NULL;
	if (list_ok(lst) && check_state((*lst)->data, 0) == PIPE)
		remove_head_node(lst);
	return (res);
}

void	print_command_tab(t_msh *ms)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (ms->cmd_tb[i] != NULL)
	{
		j = 0;
		while (ms->cmd_tb[i][j] != NULL)
		{
			printf("arg[%i][%i] %s\n", i, j, ms->cmd_tb[i][j]);
			++j;
		}
		++i;
	}
}

void	create_command_tab(t_msh *ms, t_lst **lst)
{
	int	i;

	i = 0;
	count_arg_for_tab(ms, *lst);
	printf("cmd_size %i\n", ms->parse.cmd_size);
	ms->cmd_tb = (char ***)malloc(sizeof(char **) * (ms->parse.cmd_size + 1));
	ms->redout = (t_redout *)malloc(sizeof(t_redout) * (ms->parse.cmd_size));
	ms->redin = (t_redin *)malloc(sizeof(t_redin) * (ms->parse.cmd_size));
	ms->heredoc = (t_heredoc *)malloc(sizeof(t_heredoc) * (ms->parse.cmd_size));
	if (ms->parse.cmd_size == 0 || !ms->cmd_tb || !ms->redout \
			|| !ms->redin || !ms->heredoc)
	{
		free_list(*lst);
		ft_error("Failed to malloc in struct\n", ms);
	}
	ms->cmd_tb[ms->parse.cmd_size] = NULL;
	init_redirect(ms);
	while (i < ms->parse.cmd_size)
	{
		ms->parse.arg_size = count_arg_size(ms, *lst);
		printf("arg_size is %i\n", ms->parse.arg_size);
		ms->cmd_tb[i] = insert_args(ms, lst, i);
		++i;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:16:50 by rthammat          #+#    #+#             */
/*   Updated: 2023/02/15 12:12:21 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//int	count_simple_cmd(t_msh *ms, t_lst *lst)
void	count_arg_for_tab(t_msh *ms, t_lst *lst)
{
	int	count_pipe;
	int	count_red;

	count_pipe = 0;
	count_red = 0;
	while (lst)
	{
		ms->state = check_state(lst->data, 0);
		if (ms->state == PIPE)
			++count_pipe;
		else if (is_redirect(ms, lst))
			++count_red;
		lst = lst->next;
	}
	ms->parse.cmd_size = count_pipe + 1;
	ms->parse.red_size = count_red;
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

char	**insert_args(t_msh *ms, t_lst **lst)
{
	char	**res;
	int		arg_size;
	int		i;

	arg_size = ms->parse.arg_size;
	res = (char **)malloc(sizeof(char *) * (arg_size + 1));
	i = 0;
	if (!res)
		return (NULL);
	res[arg_size] = NULL;
	while (list_ok(lst))
	{
		handle_redirect(ms, lst);
		if (!list_ok(lst) || check_state((*lst)->data, 0) == PIPE)
			break ;
		res[i++] = ft_strdup((*lst)->data);
		if (!res)
			return (NULL);
		remove_head_node(lst);
	}
	res[i] = NULL;
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
	printf("red_size %i\n", ms->parse.red_size);
	ms->cmd_tb = (char ***)malloc(sizeof(char **) * (ms->parse.cmd_size + 1));
	if (ms->parse.red_size != 0)
		ms->io_red = (t_red *)malloc(sizeof(t_red) * (ms->parse.red_size + 1));
	if (ms->parse.red_size != 0 && (!ms->cmd_tb || !ms->io_red))
	{
		free_list(*lst);
		ft_error("Failed to malloc in struct\n", ms);
	}
	ms->cmd_tb[ms->parse.cmd_size] = NULL;
	init_redirect(ms);
	while (i < ms->parse.cmd_size)
	{
		ms->parse.arg_size = count_arg_size(ms, *lst);
		printf("arg_size %i\n", ms->parse.arg_size);
		ms->cmd_tb[i] = insert_args(ms, lst);
		++i;
	}
}

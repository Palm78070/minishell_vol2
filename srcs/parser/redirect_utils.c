/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:10:02 by rthammat          #+#    #+#             */
/*   Updated: 2023/02/18 17:57:43 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	if (ms->redout[i].fd_out != -1)
	{
		if (close(ms->redout[i].fd_out) == -1)
		{
			free_list(*lst);
			ft_error("Failed to close file descripter", ms);
		}
		ms->redout[i].fd_out = -1;
	}
	if (is_env_var((*lst)->data))
	{
		ms->redout[i].filename = insert_end(*lst, (*lst)->data);
		printf("filename of redout is %s\n", ms->redout[i].filename->data);
		//printf("filename of redout is\n");
		//print_list(ms->redout[i].filename);
	}
	else
		ms->redout[i].fd_out = open((*lst)->data, O_CREAT | O_RDWR, 0777);
	printf("fd out[%i] is %i\n", i, ms->redout[i].fd_out);
}

void	parse_red_in(t_msh *ms, t_lst **lst, int i)
{
	ms->redin[i].filename = insert_end(*lst, (*lst)->data);
	printf("filename redin is\n");
	print_list(ms->redin[i].filename);
}

void	parse_heredoc(t_msh *ms, t_lst **lst, int i)
{
	if (!list_ok(lst))
		return ;
	ms->heredoc[i].delim = insert_end(*lst, (*lst)->data);
	printf("heredoc delim is\n");
	print_list(ms->heredoc[i].delim);
}

void	parse_append(t_msh *ms, t_lst **lst, int i)
{
	if (ms->append[i].fd_append != -1)
	{
		if (close(ms->append[i].fd_append) == -1)
		{
			free_list(*lst);
			ft_error("Failed to close file descripter", ms);
		}
		ms->append[i].fd_append = -1;
	}
	if (is_env_var((*lst)->data))
	{
		ms->append[i].filename = insert_end(*lst, (*lst)->data);
		printf("append is\n");
		print_list(ms->append[i].filename);
	}
	else
		ms->append[i].fd_append = open((*lst)->data, O_CREAT | O_RDWR, 0777);
	printf("append[%i] is %i\n", i, ms->append[i].fd_append);
}

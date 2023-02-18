/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 19:08:03 by rthammat          #+#    #+#             */
/*   Updated: 2023/02/18 17:15:56 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_lst *lst)
{
	t_lst	*tmp;

	tmp = lst;
	while (tmp)
	{
		lst = lst->next;
		if (tmp->data)
			free(tmp->data);
		free(tmp);
		tmp = lst;
	}
}

void	ft_error(char *s, t_msh *ms)
{
	printf("%s\n", s);
	ft_clear(ms);
	exit(EXIT_FAILURE);
}

void	free_cmd_tab(t_msh *ms)
{
	int	i;

	i = 0;
	if (ms->cmd_tb == NULL)
	{
		if (ms->cmd_tb)
			free(ms->cmd_tb);
		return ;
	}
	while (ms->cmd_tb[i] != NULL)
	{
		free_double(ms->cmd_tb[i]);
		ms->cmd_tb[i++] = NULL;
	}
	free(ms->cmd_tb[i]);
	ms->cmd_tb[i] = NULL;
	free(ms->cmd_tb);
	ms->cmd_tb = NULL;
}

void	ft_clear(t_msh *ms)
{
	if (ms != NULL)
	{
		free_cmd_tab(ms);
		free_redirect(ms);
		if (ms->line != NULL && ms->line[0] != '\0')
		{
			rl_clear_history();
			free(ms->line);
		}
		free(ms);
	}
}

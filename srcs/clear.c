/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 19:08:03 by rthammat          #+#    #+#             */
/*   Updated: 2023/02/07 16:11:14 by rthammat         ###   ########.fr       */
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

void	free_cmd_arg(t_msh *ms)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (ms->s_cmd == NULL || (ms->s_cmd && !(*ms->s_cmd)))
	{
		if (ms->s_cmd)
			free(ms->s_cmd);
		return ;
	}
	while (i < ms->parse.cmd_size)
	{
		j = 0;
		while (ms->s_cmd[i][j].arg != NULL)
		{
			if (ms->s_cmd[i][j].arg)
				free(ms->s_cmd[i][j].arg);
			++j;
		}
		free(ms->s_cmd[i][j].arg);
		free(ms->s_cmd[i]);
		++i;
	}
	free(ms->s_cmd);
}

void	free_red_str(t_msh *ms)
{
	int	i;

	i = 0;
	while (i < ms->parse.red_size)
	{
		if (ms->io_red[i].out)
			free(ms->io_red[i].out);
		if (ms->io_red[i].in)
			free(ms->io_red[i].in);
		if (ms->io_red[i].heredoc)
			free(ms->io_red[i].heredoc);
		if (ms->io_red[i].append)
			free(ms->io_red[i].append);
		++i;
	}
}

void	ft_clear(t_msh *ms)
{
	if (ms != NULL)
	{
		free_cmd_arg(ms);
		free_red_str(ms);
		if (ms->line != NULL && ms->line[0] != '\0')
		{
			//rl_clear_history(ms->line);
			free(ms->line);
		}
		if (ms->io_red)
			free(ms->io_red);
		free(ms);
	}
}

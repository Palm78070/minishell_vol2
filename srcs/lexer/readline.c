/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 16:17:21 by rthammat          #+#    #+#             */
/*   Updated: 2023/01/27 22:20:25 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rl_get(t_msh *ms)
{
	if (ms->line != NULL && *(ms->line))
	{
		free(ms->line);
		ms->line = NULL;
	}
	ms->line = readline("Enter command: ");
	if (ms->line != NULL && *(ms->line))
		add_history(ms->line);
	if (!check_error_ok(ms->line))
	{
		//printf("syntax error\n");
		rl_get(ms);
	}
}

void	rl_get_heredoc(t_msh *ms)
{
	if (ms->line_hd != NULL && *(ms->line_hd))
	{
		free(ms->line_hd);
		ms->line_hd = NULL;
	}
	ms->line_hd = readline("heredoc> ");
}

void	read_heredoc(t_msh *ms, int i, char *delim)
{
	int	count;

	count = 0;
	ms->line_hd = "\0";
	printf("i is %i\n", i);
	ms->io_red[i].heredoc = open("heredoc", O_CREAT|O_RDWR, 0644);
	printf("fd heredoc %i\n", ms->io_red[i].heredoc);
	while (1)
	{
		rl_get_heredoc(ms);
		if (ft_strncmp(ms->line_hd, delim, ft_strlen(delim)) == 0)
			break ;
		if (count > 0)
			ft_putstr_fd("\n", ms->io_red[i].heredoc);
		ft_putstr_fd(ms->line_hd, ms->io_red[i].heredoc);
		++count;
	}
}

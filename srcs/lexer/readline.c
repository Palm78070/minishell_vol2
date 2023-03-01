/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 16:17:21 by rthammat          #+#    #+#             */
/*   Updated: 2023/02/09 21:35:37 by rath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	re_prompt(t_msh *ms)
{
	if (ms->line && ms->line[0] == '\0')
	{
		free(ms->line);
		ms->line = NULL;
		return (1);
	}
	if (ms->line && *ms->line)
		if (!check_error_ok(ms->line))
			return (1);
	return (0);
}

void	rl_get(t_msh *ms)
{
	if (ms->line != NULL && *(ms->line))
	{
		free(ms->line);
		ms->line = NULL;
	}
	ms->line = readline("$ ");
	if (ms->line == NULL)
		printf("CTRL-D is pressed => EOF\n");
	if (ms->line != NULL && *(ms->line))
		add_history(ms->line);
	if (re_prompt(ms))
		rl_get(ms);
}

/*void	rl_get_heredoc(t_msh *ms)
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
	printf("i before open %i\n", i);
	printf("fd heredoc before open %i\n", ms->io_red[i].fd_heredoc);
	int	count;

	count = 0;
	if (delim == NULL)
		delim = "\0";
	ms->line_hd = "\0";
	//ms->io_red[i].fd_heredoc = open("heredoc", O_TRUNC|O_RDWR, 0644);
	ms->io_red[i].fd_heredoc = open("heredoc", O_CREAT|O_TRUNC|O_RDWR, 0644);
	printf("fd heredoc %i\n", ms->io_red[i].fd_heredoc);
	while (1)
	{
		rl_get_heredoc(ms);
		if (ft_strncmp(ms->line_hd, delim, ft_strlen(delim)) == 0)
			break ;
		if (count > 0)
			ft_putstr_fd("\n", ms->io_red[i].fd_heredoc);
		ft_putstr_fd(ms->line_hd, ms->io_red[i].fd_heredoc);
		++count;
	}
}*/

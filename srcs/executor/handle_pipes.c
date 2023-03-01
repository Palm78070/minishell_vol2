/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psutanth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:52:55 by psutanth          #+#    #+#             */
/*   Updated: 2023/03/01 15:00:03 by psutanth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**create_pipes(t_msh *ms)
{
	int	**pipes;
	int	i;

	if (ms->parse.cmd_size <= 1)
		return (NULL);
	pipes = malloc(sizeof(*pipes) * ms->parse.cmd_size);
	if (pipes == NULL)
		return (NULL);
	i = 0;
	while (i < ms->parse.cmd_size - 1)
	{
		pipes[i] = malloc(sizeof(**pipes) * 2);
		if (pipes[i] == NULL)
			continue ;
		pipe(pipes[i++]);
	}
	return (pipes);
}

void	close_pipes_index(int **pipes, int index)
{
	int	i;

	if (pipes == NULL)
		return ;
	i = 0;
	while (i < g_ms->parse.cmd_size - 1)
	{
		if (i != index)
			close(pipes[i][1]);
		if (i != index - 1)
			close(pipes[i][0]);
		++i;
	}
}

int	dup2_close(int old_fd, int new_fd)
{
	int	ret;

	ret = dup2(old_fd, new_fd);
	close(old_fd);
	return (ret);
}

void	destroy_pipes(int **pipes)
{
	int	i;

	if (pipes == NULL)
		return ;
	i = 0;
	while (i < g_ms->parse.cmd_size - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i++]);
	}
	free(pipes);
}

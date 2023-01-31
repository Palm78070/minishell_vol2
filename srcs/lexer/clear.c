/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 19:08:03 by rthammat          #+#    #+#             */
/*   Updated: 2023/01/24 21:29:17 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear(t_msh *ms)
{
	if (ms != NULL)
	{
		if (ms->line != NULL && ms->line[0] != '\0')
		{
			//rl_clear_history(ms->line);
			free(ms->line);
		}
		free(ms);
	}
}

void	ft_error(char *s, t_msh *ms)
{
	printf("%s\n", s);
	ft_clear(ms);
	exit(EXIT_FAILURE);
}

void	free_cmd_arg(t_cmd **s_cmd, int cmd_size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (s_cmd == NULL)
		return ;
	while (i < cmd_size)
	{
		j = 0;
		while (s_cmd[i][j].arg != NULL)
		{
			if (s_cmd[i][j].arg)
				free(s_cmd[i][j].arg);
			++j;
		}
		free(s_cmd[i][j].arg);
		free(s_cmd[i]);
		++i;
	}
	free(s_cmd);
}

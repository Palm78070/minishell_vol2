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

void	free_cmd_arg(t_msh *ms)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (ms->s_cmd == NULL)
		return ;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 00:02:23 by rthammat          #+#    #+#             */
/*   Updated: 2023/02/09 19:23:02 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handler(int signum)
{
	if (signum == SIGQUIT)
	{
		if (g_ms->line == NULL)
			return ;
		else
		{
			printf("CTRL-\\ is pressed => quit minishell\n");
			ft_clear(g_ms);
			exit(1);
		}
	}
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
}

void	ft_signal(t_msh *ms)
{
	sigaction(SIGINT, &ms->sa, 0);
	sigaction(SIGQUIT, &ms->sa, 0);
}

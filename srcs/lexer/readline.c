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

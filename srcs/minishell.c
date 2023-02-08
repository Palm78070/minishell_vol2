/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 19:44:51 by rthammat          #+#    #+#             */
/*   Updated: 2023/02/08 23:22:44 by rath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_msh	*ms;

void	ft_handler(int signum)
{
	if (signum == SIGQUIT)
	{
		//ft_clear(ms);
		// exit(1);
		return ;
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

void	init_struct(t_msh *ms)
{
	ms->line = NULL;
	ms->s_cmd = NULL;
	ms->io_red = NULL;
	ms->parse.red_size = 0;
	sigemptyset(&ms->sa.sa_mask);
	sigaddset(&ms->sa.sa_mask, SIGQUIT);
	ms->sa.sa_flags = SA_SIGINFO;
	ms->sa.sa_handler = ft_handler;
}

int	main(void)
{
	t_lst	*lst;

	lst = NULL;
	ms = (t_msh *)malloc(sizeof(t_msh));
	if (!ms)
		ft_error("Fail to malloc struct", ms);
	init_struct(ms);
	while (1)
	{
		sigaction(SIGINT, &ms->sa, 0);
		rl_get(ms);
		if (ms->line && ft_strncmp(ms->line, "exit", ft_strlen("exit")) == 0)
			break ;
		printf("input from readline %s\n", ms->line);
		lst = ft_lexer(ms);
		//printf("test ms->line %s\n", ms->line);
		ft_parsing(ms, &lst);
		print_list(lst);
		free_list(lst);
	}
	ft_clear(ms);
	return (0);
}

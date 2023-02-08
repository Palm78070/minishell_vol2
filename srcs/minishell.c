/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 19:44:51 by rthammat          #+#    #+#             */
/*   Updated: 2023/02/09 03:04:05 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_msh	*ms;

void	ft_handler(int signum)
{
	if (signum == SIGQUIT)
	{
		//printf("hello\n");
		/*rl_replace_line("", 0);
		rl_redisplay();*/
		return ;
	}
	if (signum == SIGINT)
	{
		(void)signum;
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
	ms->sa.sa_flags = SA_SIGINFO;
	ms->sa.sa_handler = ft_handler;
}

int	is_quit(t_msh *ms)
{
	if (ms->line == NULL \
		|| ft_strncmp(ms->line, "exit", ft_strlen("exit")) == 0)
		return (1);
	return (0);
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
		ft_signal(ms);
		rl_get(ms);
		if (is_quit(ms))
			break ;
		printf("input from readline %s\n", ms->line);
		lst = ft_lexer(ms);
		ft_parsing(ms, &lst);
		print_list(lst);
		free_list(lst);
	}
	free_list(lst);
	ft_clear(ms);
	return (0);
}

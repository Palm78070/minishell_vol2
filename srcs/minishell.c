/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 19:44:51 by rthammat          #+#    #+#             */
/*   Updated: 2023/02/09 20:44:25 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct(void)
{
	g_ms->line = NULL;
	g_ms->s_cmd = NULL;
	g_ms->io_red = NULL;
	g_ms->parse.red_size = 0;
	sigemptyset(&g_ms->sa.sa_mask);
	g_ms->sa.sa_flags = SA_SIGINFO;
	g_ms->sa.sa_handler = ft_handler;
}

int	is_quit(void)
{
	if (g_ms->line == NULL \
		|| ft_strncmp(g_ms->line, "exit", ft_strlen("exit")) == 0)
		return (1);
	return (0);
}

int	main(void)
{
	t_lst	*lst;
	// struct	termios old_set, new_set;
	// tcgetattr(STDIN_FILENO, &old_set);
	// new_set = old_set;
	// new_set.c_lflag &= (~ICANON);
	// tcsetattr(STDIN_FILENO, TCSANOW, &new_set);
	lst = NULL;
	g_ms = (t_msh *)malloc(sizeof(t_msh));
	if (!g_ms)
		ft_error("Fail to malloc struct", g_ms);
	init_struct();
	rl_catch_signals = 0;
	while (1)
	{
		ft_signal(g_ms);
		rl_get(g_ms);
		if (is_quit())
			break ;
		printf("input from readline %s\n", g_ms->line);
		lst = ft_lexer(g_ms);
		ft_parsing(g_ms, &lst);
		print_list(lst);
		free_list(lst);
	}
	free_list(lst);
	ft_clear(g_ms);
	//tcsetattr(STDIN_FILENO, TCSANOW, &old_set);
	return (0);
}

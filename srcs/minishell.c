/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 19:44:51 by rthammat          #+#    #+#             */
/*   Updated: 2023/03/01 15:11:31 by psutanth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_msh	*g_ms;

void	init_struct(void)
{
	g_ms->redout = NULL;
	g_ms->redin = NULL;
	g_ms->heredoc = NULL;
	g_ms->line = NULL;
	g_ms->cmd_tb = NULL;
	g_ms->parse.cmd_size = 0;
	g_ms->parse.arg_size = 0;
	//sigemptyset(&g_ms->sa.sa_mask);
	//g_ms->sa.sa_flags = 0;
	//g_ms->sa.sa_handler = ft_handler;
	g_ms->sa = init_sa(ft_handler);
	g_ms->sa_child = init_sa(ft_handler_child);
	g_ms->should_exit = 0;
	g_ms->estatus = 0;
}

int	is_quit(void)
{
	if (g_ms->line == NULL \
		|| ft_strncmp(g_ms->line, "exit", ft_strlen("exit")) == 0)
		return (1);
	return (0);
}

static void	init_values(int argc, char **argv, int *result)
{
	(void)argc;
	(void)argv;
	*result = 0;
	rl_catch_signals = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_lst	*lst;
	int		result;

	init_values(argc, argv, &result);
	lst = NULL;
	g_ms = (t_msh *)malloc(sizeof(t_msh));
	if (!g_ms)
		ft_error("Fail to malloc struct", g_ms);
	init_struct();
	while (result == 0 && g_ms->should_exit == 0)
	{
		ft_signal(g_ms->sa);
		rl_get(g_ms);
		lst = ft_lexer(g_ms);
		result = ft_parsing(g_ms, &lst, envp);
		free_list(lst);
	}
	free_list(lst);
	if (result == 0 && g_ms->should_exit == 1)
		result = g_ms->estatus;
	ft_clear(g_ms);
	return (result);
}

/*int	main(int argc, char **argv)
{
 	if (argc != 2)
 		return (2);
 	t_lst	*lst;
 	lst = NULL;
 	g_ms = (t_msh *)malloc(sizeof(t_msh));
 	if (!g_ms)
 		ft_error("Fail to malloc struct", g_ms);
 	init_struct();
 	rl_catch_signals = 0;
 	while (1)
 	{
 		ft_signal(g_ms);
 		//rl_get(g_ms);
 		printf("argv[1] %s\n", argv[1]);
 		int fd = open(argv[1], O_RDONLY);
 		g_ms->line = get_next_line(fd);
 		if (is_quit())
 			break ;
 		printf("input from readline %s\n", g_ms->line);
 		lst = ft_lexer(g_ms);
 		ft_parsing(g_ms, &lst);
 		print_list(lst);
 		free_list(lst);
 		break ;
 	}
 	free(g_ms->line);
 	g_ms->line = NULL;
 	free_list(lst);
 	ft_clear(g_ms);
	return (0);
 }*/

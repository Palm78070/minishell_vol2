/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 19:44:51 by rthammat          #+#    #+#             */
/*   Updated: 2023/02/03 14:31:44 by rath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_msh	*ms;

void	ft_handler(int signum)
{
	if (signum == SIGQUIT)
	{
		// ft_clear(ms);
		// exit(1);
		return ;
	}
}

//int	main(void)
/*int	main(int argc, char **argv)
{
	t_lst	*lst;

	lst = NULL;
	ms = (t_msh *)malloc(sizeof(t_msh));
	if (!ms)
		ft_error("Fail to malloc struct", ms);
	if (argc != 2)
		return (0);
	// sigemptyset(&ms->sa.sa_mask);
	// sigaddset(&ms->sa.sa_mask, SIGQUIT);
	// ms->sa.sa_handler = ft_handler;
	// sigaction(SIGQUIT, &ms->sa, 0);
	int	fd = open(argv[1], O_RDONLY);
	ms->line = "\0";
	//while (ms->line != NULL)
	while (1)
	{
		//rl_get(ms);
		ms->line = get_next_line(fd);
		//printf("ms->line %s\n", ms->line);
		if (ms->line && is_exit(ms->line))
			break ;
		printf("input from readline %s\n", ms->line);
		lst = ft_lexer(ms);
		//printf("test ms->line %s\n", ms->line);
		create_command_tab(ms, &lst);
		print_list(lst);
		free_list(lst);
		break ;
	}
	free(ms->line);
	ms->line = NULL;
	ms->line = get_next_line(fd);
	free(ms->line);
	ft_clear(ms);
	return (0);
}*/

void	init_struct(t_msh *ms)
{
	ms->line = NULL;
	ms->s_cmd = NULL;
	ms->io_red = NULL;
}

int	main(void)
{
	t_lst	*lst;

	lst = NULL;
	ms = (t_msh *)malloc(sizeof(t_msh));
	if (!ms)
		ft_error("Fail to malloc struct", ms);
	// sigemptyset(&ms->sa.sa_mask);
	// sigaddset(&ms->sa.sa_mask, SIGQUIT);
	// ms->sa.sa_handler = ft_handler;
	// sigaction(SIGQUIT, &ms->sa, 0);
	//ms->line = NULL;
	init_struct(ms);
	while (1)
	{
		rl_get(ms);
		if (ms->line && ft_strncmp(ms->line, "exit", ft_strlen("exit")) == 0)
			break ;
		printf("input from readline %s\n", ms->line);
		lst = ft_lexer(ms);
		//printf("test ms->line %s\n", ms->line);
		/*ms->parse.cmd_size = count_simple_cmd(ms, lst);
		printf("cmd_size %i\n", ms->parse.cmd_size);
		ms->s_cmd = (t_cmd **)malloc(sizeof(t_cmd *) * ms->parse.cmd_size);
		int	i = 0;
		while (i < ms->parse.cmd_size)
		{
			ms->parse.arg_size = count_arg_size(ms, lst);
			printf("arg_size %i\n", ms->parse.arg_size);
			ms->s_cmd[i] = insert_args(ms, &lst);
			++i;
		}*/
		/*create_command_tab(ms, &lst);
		print_arg(ms);
		free_cmd_arg(ms);*/
		ft_parsing(ms, &lst);
		print_list(lst);
		free_list(lst);
	}
	ft_clear(ms);
	return (0);
}

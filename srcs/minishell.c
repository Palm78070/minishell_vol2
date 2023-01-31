/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 19:44:51 by rthammat          #+#    #+#             */
/*   Updated: 2023/01/30 23:55:46 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_msh	*ms;

int	is_exit(char *s)
{
	if (s[0] == 'e' && s[1] == 'x' && s[2] == 'i' && s[3] == 't'
		&& s[4] == '\0')
	{
		printf("exit\n");
		return (1);
	}
	return (0);
}

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
		int	cmd_size = count_simple_cmd(ms, lst);
		printf("cmd_size %i\n", cmd_size);
		t_cmd	**s_cmd = (t_cmd **)malloc(sizeof(t_cmd *) * cmd_size);
		
		int	i = 0;
		while (i < cmd_size)
		{
			int arg_size = count_arg_size(ms, lst);
			printf("arg_size %i\n", arg_size);
			s_cmd[i] = insert_args(ms, &lst, arg_size);
			print_arg(s_cmd[i]);
			++i;
		}
		free_cmd_arg(s_cmd, cmd_size);
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
	ms->line = NULL;
	while (1)
	{
		rl_get(ms);
		if (ms->line && is_exit(ms->line))
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
		create_command_tab(ms, &lst);
		print_arg(ms);
		free_cmd_arg(ms);
		print_list(lst);
		free_list(lst);
	}
	ft_clear(ms);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 16:17:21 by rthammat          #+#    #+#             */
/*   Updated: 2023/02/09 04:07:53 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_error_ok(char *s)
{
	char	c;
	int	flag;
	int	i;

	c = 0;
	i = 0;
	if (!quote_error_ok(s, &c))
		return (0);
	flag = arrow_error_ok(s, &c, &i);
	if (flag == -1)
	{
		flag = 0;
		printf("syntax error near unexpected token '");
		while (s[i] && s[i] == c && flag++ != 3)
			printf("%c", s[i++]);
		printf("'\n");
		return (0);
	}
	else if (flag == 0)
		printf("syntax error near unexpected token 'newline'\n");
	if (!pipe_error_ok(s) || flag <= 0)
		return (0);
	return (1);
}

void	check_quit(t_msh *ms)
{
	int	i;

	i = 0;
	if (ms->line == NULL)
		printf("CTRL-D is pressed => EOF\n");
	while (ms->line && ms->line[i])
	{
		if (ms->line[i] == 4)
		{
			printf("SIGQUIT\n");
			ms->line = NULL;
		}
		++i;
	}
}

void	hit_newline(t_msh *ms)
{
	if (ms->line && *ms->line == '\0')
	{
		printf("xxx\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	rl_get(t_msh *ms)
{
	if (ms->line != NULL && *(ms->line))
	{
		free(ms->line);
		ms->line = NULL;
	}
	ms->line = readline("Enter command: ");
	//hit_newline(ms);
	if (ms->line == NULL)
		printf("CTRL-D is pressed => EOF\n");
	if (ms->line != NULL && *(ms->line))
		add_history(ms->line);
	if (ms->line && *ms->line && !check_error_ok(ms->line))
		rl_get(ms);
}

/*void	rl_get_heredoc(t_msh *ms)
{
	if (ms->line_hd != NULL && *(ms->line_hd))
	{
		free(ms->line_hd);
		ms->line_hd = NULL;
	}
	ms->line_hd = readline("heredoc> ");
}

void	read_heredoc(t_msh *ms, int i, char *delim)
{
	printf("i before open %i\n", i);
	printf("fd heredoc before open %i\n", ms->io_red[i].fd_heredoc);
	int	count;

	count = 0;
	if (delim == NULL)
		delim = "\0";
	ms->line_hd = "\0";
	//ms->io_red[i].fd_heredoc = open("heredoc", O_TRUNC|O_RDWR, 0644);
	ms->io_red[i].fd_heredoc = open("heredoc", O_CREAT|O_TRUNC|O_RDWR, 0644);
	printf("fd heredoc %i\n", ms->io_red[i].fd_heredoc);
	while (1)
	{
		rl_get_heredoc(ms);
		if (ft_strncmp(ms->line_hd, delim, ft_strlen(delim)) == 0)
			break ;
		if (count > 0)
			ft_putstr_fd("\n", ms->io_red[i].fd_heredoc);
		ft_putstr_fd(ms->line_hd, ms->io_red[i].fd_heredoc);
		++count;
	}
}*/

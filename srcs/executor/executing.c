/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psutanth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:38:18 by psutanth          #+#    #+#             */
/*   Updated: 2023/03/01 15:13:46 by psutanth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_fail_exit_code(void)
{
	if (errno == ENOENT)
		return (127);
	if (errno == EACCES)
		return (126);
	return (1);
}

static int	is_builtin(char *cmd)
{
	return (ft_strncmp(cmd, "exit", ft_strlen(cmd) + 1) == 0
		|| ft_strncmp(cmd, "echo", ft_strlen(cmd) + 1) == 0
		|| ft_strncmp(cmd, "pwd", ft_strlen(cmd) + 1) == 0);
}

static int	run_builtin(char *builtin, char **argv)
{
	if (ft_strncmp(builtin, "pwd", ft_strlen(builtin) + 1) == 0)
		return (builtin_pwd());
	if (ft_strncmp(builtin, "echo", ft_strlen(builtin) + 1) == 0)
		return (builtin_echo(argv));
	return (0);
}

static int	fork_subroutine(t_msh *ms, char **envp, int **pipes, int index)
{
	int	ret;

	if (pipes != NULL)
	{
		close_pipes_index(pipes, index);
		if (index < ms->parse.cmd_size - 2)
			dup2_close(pipes[index][1], STDOUT_FILENO);
		if (index > 0)
			dup2_close(pipes[index - 1][0], STDIN_FILENO);
	}
	ms->should_exit = 2;
	if (is_builtin(ms->cmd_tb[index][0]))
		ret = run_builtin(ms->cmd_tb[index][0], ms->cmd_tb[index]);
	else
	{
		ft_execvpe(ms->cmd_tb[index][0], ms->cmd_tb[index], envp);
		ret = get_fail_exit_code();
	}
	destroy_pipes(pipes);
	return (ret);
}

int	ft_execute(t_msh *ms, char **envp)
{
	int		**pipes;
	int		i;
	pid_t	last_proc;
	
	ft_signal(ms->sa_child);
	if (ft_strncmp(ms->cmd_tb[0][0], "exit", 5) == 0)
	{
		ms->should_exit = 1;
		return (0);
	}
	pipes = create_pipes(ms);
	if (pipes == NULL && ms->parse.cmd_size > 1)
		return (1);
	i = 0;
	while (i < ms->parse.cmd_size)
	{
		last_proc = fork();
		if (last_proc == 0)
			return (fork_subroutine(ms, envp, pipes, i));
		++i;
	}
	destroy_pipes(pipes);
	while (wait(NULL) != -1)
		continue ;
	return (0);
}

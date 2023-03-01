/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execvpe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psutanth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:41:13 by psutanth          #+#    #+#             */
/*   Updated: 2023/03/01 09:15:57 by psutanth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_path(char *path, char *progname)
{
	char	*partial;
	char	*full;

	partial = ft_strjoin(path, "/");
	full = ft_strjoin(partial, progname);
	free(partial);
	return (full);
}

static int	try_exec(char *path, char *progname, char **argv, char **envp)
{
	char	*full_path;
	char	*temp;

	full_path = join_path(path, progname);
	if (full_path == NULL)
		return (1);
	temp = argv[0];
	argv[0] = full_path;
	execve(full_path, argv, envp);
	free(full_path);
	argv[0] = temp;
	if (errno != ENOENT)
		return (-1);
	return (0);
}

int	ft_execvpe(char *progname, char **argv, char **envp)
{
	char	*temp;
	char	**paths;
	size_t	i;

	if (execve(progname, argv, envp) == -1 && errno != ENOENT)
		return (-1);
	temp = get_envp_value("PATH", envp);
	if (temp == NULL)
		return (-1);
	paths = ft_split(temp, ':');
	i = 0;
	while (paths[i] != NULL)
	{
		if (try_exec(paths[i++], progname, argv, envp) == -1)
			break ;
	}
	free_strarr(paths);
	return (-1);
}

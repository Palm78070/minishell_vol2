/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psutanth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:55:35 by psutanth          #+#    #+#             */
/*   Updated: 2023/02/28 12:08:16 by psutanth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_arg(t_msh *ms, size_t i, size_t *j, char **envp)
{
	char	*expanded;

	expanded = try_expand_var(ms->cmd_tb[i][*j], envp);
	if (expanded == NULL)
		++*j;
	else if (expanded[0] == '\0')
	{
		printf("arg[%lu][%lu] is empty, removing\n", i, *j);
		splice_char_array(&ms->cmd_tb[i], *j);
		free(expanded);
	}
	else
	{
		expanded = remove_quote(expanded);
		if (expanded == NULL)
			expanded = ft_strdup("");
		free(ms->cmd_tb[i][*j]);
		ms->cmd_tb[i][(*j)++] = expanded;
	}
}

int	ft_expand(t_msh *ms, char **envp)
{
	size_t	i;
	size_t	j;
	int		result;

	result = expand_redin(ms->redin, ms->parse.cmd_size, envp);
	if (result != 0)
	{
		if (result == -1)
			perror("redirect error");
		return (1);
	}
	if (expand_redout(ms->redout, ms->parse.cmd_size, envp))
	{
		printf("error: invalid filename\n");
		return (1);
	}
	i = -1;
	while (ms->cmd_tb[++i] != NULL)
	{
		j = 0;
		while (ms->cmd_tb[i][j] != NULL)
			expand_arg(ms, i, &j, envp);
	}
	return (0);
}

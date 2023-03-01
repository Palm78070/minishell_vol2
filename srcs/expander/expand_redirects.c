/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psutanth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:21:46 by psutanth          #+#    #+#             */
/*   Updated: 2023/02/28 12:22:08 by psutanth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_strip_quote(char *str, char **envp)
{
	char	*expanded;

	expanded = try_expand_var(str, envp);
	expanded = remove_quote(expanded);
	if (expanded == NULL || *expanded == '\0')
	{
		free(expanded);
		return (NULL);
	}
	return (expanded);
}

static void	free_and_replace(char **dst, char *src)
{
	free(*dst);
	*dst = src;
}

// returns 1 if expansion creates empty string
int	expand_redout(t_redout *redout, int cmdsize, char **envp)
{
	t_lst	*lst;
	int		i;
	char	*exp;

	i = -1;
	while (++i < cmdsize)
	{
		lst = redout[i].filename;
		while (lst != NULL)
		{
			exp = expand_strip_quote(lst->data, envp);
			if (exp == NULL)
				return (1);
			free_and_replace(&lst->data, exp);
			if (redout[i].append)
				redout[i].fd_out = open(exp, O_CREAT | O_RDWR | O_APPEND, 0);
			else
				redout[i].fd_out = open(exp, O_CREAT | O_RDWR, 0);
			if (lst->next != NULL)
				close(redout[i].fd_out);
			lst = lst->next;
		}
	}
	return (0);
}

int	expand_redin(t_redin *redin, int cmdsize, char **envp)
{
	t_lst	*lst;
	int		i;
	char	*expanded;

	i = -1;
	while (++i < cmdsize)
	{
		lst = redin[i].filename;
		while (lst != NULL)
		{
			expanded = expand_strip_quote(lst->data, envp);
			if (expanded == NULL)
				return (1);
			free_and_replace(&lst->data, expanded);
			if (lst->next == NULL)
				break ;
			lst = lst->next;
		}
		if (lst == NULL)
			continue ;
		redin[i].fd_in = open(lst->data, O_RDONLY, 0);
		if (redin[i].fd_in == -1)
			return (-1);
	}
	return (0);
}

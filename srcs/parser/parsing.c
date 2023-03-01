/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:02:53 by rthammat          #+#    #+#             */
/*   Updated: 2023/03/01 15:11:24 by psutanth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parsing(t_msh *ms, t_lst **lst, char **envp)
{
	int	retval;

	retval = 0;
	create_command_tab(ms, lst);
	if (ft_expand(ms, envp) == 0)
		retval = ft_execute(ms, envp);
	free_redirect(ms);
	free_cmd_tab(ms);
	return (retval);
}

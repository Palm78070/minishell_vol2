/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:02:53 by rthammat          #+#    #+#             */
/*   Updated: 2023/02/18 02:10:05 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parsing(t_msh *ms, t_lst **lst)
{
	create_command_tab(ms, lst);
	print_command_tab(ms);
	free_cmd_tab(ms);
}

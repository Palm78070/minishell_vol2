/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 21:06:33 by rthammat          #+#    #+#             */
/*   Updated: 2023/02/07 15:04:32 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_metachar(int i)
{
	if (i == PIPE
		|| i == REDIRECT_I
		|| i == REDIRECT_O
		|| i == HEREDOC
		|| i == APPEND)
		return (1);
	return (0);
}

t_lst	*remove_space(t_lst *lst)
{
	t_lst	*ptr;

	ptr = lst;
	while (ptr && ptr->data)
	{
		if (list_ok(&ptr) && is_all_space(ptr->data))
		{
			ft_remove_if_addr(&lst, ptr->data);
			ptr = lst;
		}
		else
			ptr = ptr->next;
	}
	return (lst);
}

t_lst	*ft_lexer(t_msh *ms)
{
	t_lst	*lst;

	lst = ft_token(ms);
	lst = remove_space(lst);
	lst = handle_quote(lst);
	return (lst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 21:06:33 by rthammat          #+#    #+#             */
/*   Updated: 2023/02/01 14:22:42 by rath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_metachar(int i)
{
	return (i == PIPE || i == REDIRECT_I || i == REDIRECT_O || i == HEREDOC || i == APPEND);
}

t_lst	*remove_space(t_lst *lst)
{
	t_lst	*ptr;

	ptr = lst;
	while (ptr && ptr->data)
	{
		if (is_all_space(ptr->data) && ptr->next)
		{
			if (is_metachar(check_state(ptr->next->data, 0)))
			{
				ft_remove_if_addr(&lst, ptr->data);
				ptr = lst;
			}
		}
		else if (is_metachar(check_state(ptr->data, 0)) && ptr->next)
		{
			if (is_all_space(ptr->next->data))
			{
				ft_remove_if_addr(&lst, ptr->next->data);
				ptr = lst;
			}
		}
		ptr = ptr->next;
	}
	return (lst);
}

t_lst	*ft_lexer(t_msh *ms)
{
	t_lst	*lst;

	lst = ft_token(ms);
	lst = handle_quote(lst);
	lst = remove_space(lst);
	return (lst);
}
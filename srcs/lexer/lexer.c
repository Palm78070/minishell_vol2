/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 21:06:33 by rthammat          #+#    #+#             */
/*   Updated: 2023/01/27 20:32:22 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*ft_lexer(t_msh *ms)
{
	t_lst	*lst;
	t_lst	*ptr;

	lst = ft_token(ms);
	ptr = lst;
	while (ptr)
	{
		ptr->data = remove_quote(ptr->data);
		ptr = ptr->next;
	}
	return (lst);
}

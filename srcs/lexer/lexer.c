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

/*int	is_all_space(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
	{
		if (!ft_isspace(s[i]))
			return (0);
		++i;
	}
	return (1);
}

void	ft_remove_if_space(t_lst **lst)
{
	t_lst	*curr;

	curr = *lst;
	if (lst == NULL || *lst == NULL)
		return ;
	if (curr->data[0] == ' ')
	{
		*lst = curr->next;
		if (curr && curr->data)
			free(curr->data);
		if (curr)
			free(curr);
		ft_remove_if_space(lst);
	}
	else
		ft_remove_if_space(&curr->next);
}*/

t_lst	*ft_lexer(t_msh *ms)
{
	t_lst	*lst;
	t_lst	*ptr;

	lst = ft_token(ms);
	ptr = lst;
	while (ptr)
	{
		//ms->state = check_state(ptr->data, 0);
		//if (ms->state == S_QUOTE || ms->state == D_QUOTE)
		//{
			//printf("xxx\n");
			//ms->state = check_state(ptr->data, 1);
			//if (ms->state == 0)
				ptr->data = remove_quote(ptr->data);
		//}
		ptr = ptr->next;
	}
	//ft_remove_if_space(&lst);
	return (lst);
}

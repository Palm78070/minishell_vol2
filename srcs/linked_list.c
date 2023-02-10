/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 00:22:50 by rthammat          #+#    #+#             */
/*   Updated: 2023/01/30 23:51:02 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_lst *lst)
{
	if (lst == NULL)
	{
		printf("list is NULL\n");
		return ;
	}
	printf("lexer %s\n", lst->data);
	print_list(lst->next);
}

t_lst	*create_node(char *s)
{
	t_lst	*ptr;

	if (s != NULL && s[0] == '\0')
		return (NULL);
	ptr = (t_lst *)malloc(sizeof(t_lst));
	if (!ptr)
		return (NULL);
	if (s == NULL)
		ptr->data = NULL;
	else
		ptr->data = ft_strdup(s);
	ptr->next = NULL;
	return (ptr);
}

t_lst	*insert_end(t_lst *lst, char *s)
{
	if (lst == NULL)
	{
		lst = create_node(s);
		return (lst);
	}
	lst->next = insert_end(lst->next, s);
	return (lst);
}

void	remove_head_node(t_lst **lst)
{
	t_lst	*curr;

	curr = *lst;
	if (!list_ok(lst))
		return ;
	else
	{
		*lst = curr->next;
		free(curr->data);
		free(curr);
		return ;
	}
}

int	list_ok(t_lst **lst)
{
	if (lst && *lst && (*lst)->data)
		return (1);
	return (0);
}

void	ft_remove_if_addr(t_lst **lst, char *data)
{
	t_lst	*curr;

	if (!(list_ok(lst)))
		return ;
	curr = *lst;
	if ((curr && curr->data == data))
	{
		*lst = curr->next;
		free(curr->data);
		free(curr);
		ft_remove_if_addr(lst, data);
	}
	else
		ft_remove_if_addr(&curr->next, data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 00:22:50 by rthammat          #+#    #+#             */
/*   Updated: 2023/01/16 00:28:31 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_lst *lst)
{
	if (lst == NULL)
	{
		free(lst);
		lst = NULL;
		return ;
	}
	free(lst->data);
	lst->data = NULL;
	free_list(lst->next);
}

void	print_list(t_lst *lst)
{
	if (lst == NULL)
		return ;
	printf("lexer %s\n", lst->data);
	print_list(lst->next);
}

t_lst	*create_node(char *s)
{
	t_lst	*ptr;

	if (s[0] == '\0')
		return (NULL);
	ptr = (t_lst *)malloc(sizeof(t_lst));
	if (!ptr)
		return (NULL);
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
/*
int	main(void)
{
	t_lst	*lst;

	lst = (t_lst *)malloc(sizeof(t_lst));
	if (!lst)
		exit(1);
	lst = NULL;
	lst = insertEnd(lst, "abc");
	lst = insertEnd(lst, "def");
	lst = insertEnd(lst, "ghi");
	lst = insertEnd(lst, "jk");
	print_list(lst);
	free_list(lst);
	return (0);
}*/

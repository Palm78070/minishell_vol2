/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 21:06:33 by rthammat          #+#    #+#             */
/*   Updated: 2023/01/26 14:05:54 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//t_lst	*ft_lexer(t_msh *ms)
t_lst	*ft_token(t_msh *ms)
{
	int		i;
	t_lst	*lst;

	i = 0;
	lst = NULL;
	while (ms->line && ms->line[i])
	{
		ms->state = check_state(ms->line, i);
		if (ms->state == SP)
			lst = token_space(ms, lst, &i);
		else if (ms->state == PIPE)
			lst = token_pipe(ms, lst, &i);
		else if (ms->state == S_QUOTE || ms->state == D_QUOTE)
			lst = token_quote(ms, lst, &i);
		else if (ms->state == REDIRECT_I || ms->state == REDIRECT_O)
			lst = token_redirect(ms, lst, &i);
		else if (ms->state == HEREDOC || ms->state == APPEND
			|| ms->state == AND_IF || ms->state == OR_IF)
			lst = token_double_sign(ms, lst, &i);
		else
			++i;
	}
	if (ms->line && ms->line[0])
		lst = insert_str(ms, lst, i);
	return (lst);
}

void	ft_remove_and_join(t_lst **lst, char *check_point, t_msh *ms, int (*f)(t_msh *, char *))
{
	t_lst	*curr;
	t_lst	*new_node;

	curr = *lst;
	new_node = NULL;
	if (lst == NULL || *lst == NULL)
		return ;
	if (f(ms, curr->data) && curr->next && curr->next->data != check_point)
	{
		ms->dummy = join_text(ms, ms->dummy, curr->data);
		if ((ms->dummy && curr->next && !f(ms, curr->next->data)) || (curr->next == NULL && ms->dummy))
		{
			if (curr->next)
				check_point = curr->next->data;
			new_node = create_node(ms->dummy);
			new_node->next = curr->next;
			*lst = new_node;
			free(ms->dummy);
			ms->dummy = NULL;
		}
		else
			*lst = curr->next;
		free(curr->data);
		free(curr);
		ft_remove_and_join(lst, check_point, ms, f);
	}
	else
		ft_remove_and_join(&curr->next, check_point, ms, f);
}

t_lst	*dummy(t_msh *ms, t_lst *lst, int (*f)(t_msh *, char *))
{
	t_lst	*ptr;
	char	*check_point;

	ptr = lst;
	ms->dummy = NULL;
	check_point = NULL;

	while (ptr)
	{
		if (ptr && f(ms, ptr->data))
		{
			while (ptr && f(ms, ptr->data))
			{
				ft_remove_and_join(&lst, check_point, ms, f);
				ptr = lst;
				break ;
			}
			break ;
		}
		else
			ptr = ptr->next;
	}
	return (lst);
}

int	is_blank_quote(t_msh *ms, char *s)
{
	int	i;
	char	quote;

	i = 0;
	quote = 0;
	if (ms->state == S_QUOTE)
		quote = '\'';
	else if (ms->state == D_QUOTE)
		quote = '"';
	while (s[i])
	{
		if (s[i] != quote)
			return (0);
		++i;
	}
	return (1);
}

t_lst	*remove_blank_quote(t_msh *ms, t_lst *lst)
{
	t_lst	*ptr;

	ptr = lst;
	while (ptr)
	{
		printf("ptr->data %s\n", ptr->data);
		if (ptr && is_blank_quote(ms, ptr->data))
		{
			printf("xxx\n");
			ft_remove_if_addr(&lst, ptr->data);	
			ptr = lst;
		}
		else
		{
			printf("ptr->data2 %s\n", ptr->data);
			ptr = ptr->next;
		}
	}
	return (lst);
}

t_lst	*ft_lexer(t_msh *ms)
{
	t_lst *lst;

	lst = ft_token(ms);
	lst = remove_blank_quote(ms, lst);
	lst = dummy(ms, lst, &quote_joinable);
	lst = dummy(ms, lst, &is_all_plain_text);
	//lst = quote_assemble(ms, lst);
	//lst = plain_text_assemble(ms, lst);
	return (lst);
}

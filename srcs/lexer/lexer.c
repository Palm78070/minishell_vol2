/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 21:06:33 by rthammat          #+#    #+#             */
/*   Updated: 2023/01/25 03:28:20 by rath             ###   ########.fr       */
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

/*int	dollar_sign(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == '\'')
		++i;
	while (s[i] && ft_isspace(s[i]))
		++i;
	if (s[i] == '$')
		return (1);
	return (0);
}

int	quote_joinable(t_msh *ms, char *s)
{
	int	i;

	i = 0;
	ms->state = check_state(s, 0);
	if (ms->state == D_QUOTE || (ms->state == S_QUOTE && !dollar_sign(s)))
		return (1);
	return (0);
}

void	ft_remove_if_addr(t_lst **lst, char *data)
{
	t_lst	*curr;

	curr = *lst;
	if (lst == NULL || *lst == NULL)
		return ;
	if (curr->data == data)
	{
		*lst = curr->next;
		free(curr->data);
		free(curr);
		ft_remove_if_addr(lst, data);
	}
	else
		ft_remove_if_addr(&curr->next, data);
}

void	ft_insert_if_addr(t_lst **lst, char *cmp, char *data)
{
	t_lst	*curr;
	t_lst	*new_node;

	curr = *lst;
	new_node = NULL;
	if (lst == NULL || *lst == NULL)
		return ;
	if (curr->next->data == cmp)
	{
		new_node = create_node(data);
		new_node->next = curr->next;
		*lst = new_node;
		free(curr->data);
		free(curr);
		ft_insert_if_addr(&((*lst)->next->next), cmp, data);
	}
	else
		ft_insert_if_addr(&curr->next, cmp, data);
}

t_lst	*insert_before_target(t_lst *lst, char *cmp, char *data)
{
	t_lst	*tmp;
	t_lst	*new_node;

	if (cmp == NULL)
	{
		lst = insert_end(lst, data);
		return (lst);
	}
	new_node = create_node(data);
	tmp = lst;
	if (lst == NULL)
		return (NULL);
	while (tmp)
	{
		if (tmp && tmp->data == cmp)
		{
			new_node->next = tmp;
			lst = new_node;
			break ;
		}
		if (tmp->next && tmp->next->data == cmp)
		{
			new_node->next = tmp->next;
			tmp->next = new_node;
			break ;
		}
		tmp = tmp->next;
	}
	return (lst);
}

char	*join_text(t_msh *ms, char *res_text, char *data)
{
	char	*tmp;
	char	*new_text;

	tmp = NULL;
	new_text = NULL;
	if (ms->state == S_QUOTE || ms->state == D_QUOTE)
	{
		if (data[1] == '\'' || data[1] == '"')
			new_text = NULL;
		else if (ms->state == S_QUOTE)
			new_text = ft_strtrim(data, "'");
		else
			new_text = ft_strtrim(data, "\"");
	}
	else
		new_text = data;
	tmp = res_text;
	res_text = ft_strjoin(res_text, new_text);
	if (new_text && (ms->state == S_QUOTE || ms->state == D_QUOTE))
		free(new_text);
	if (tmp && *tmp != '\0')
		free(tmp);
	return (res_text);
}

int	is_all_plain_text(t_msh *ms, char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
	{
		ms->state = check_state(s, i);
		if (ms->state != 0)
			return (0);
		++i;
	}
	return (1);
}

t_lst	*insert_new_token(t_msh *ms, t_lst *lst, char *res, t_lst *ptr)
{
	if (ptr && res && *res && !quote_joinable(ms, ptr->data))
		lst = insert_before_target(lst, ptr->data, res);
	else if (ptr && res && *res && !is_all_plain_text(ms, ptr->data))
		lst = insert_before_target(lst, ptr->data, res);
	else if (ptr == NULL)
		lst = insert_before_target(lst, NULL, res);
	return (lst);
}

t_lst	*quote_assemble(t_msh *ms, t_lst *lst)
{
	t_lst	*ptr;
	t_lst	*tmp;
	char	*res;

	ptr = lst;
	res = NULL;
	while (ptr)
	{
		if (quote_joinable(ms, ptr->data))
		{
			while (ptr && quote_joinable(ms, ptr->data))
			{
				tmp = ptr;
				ptr = ptr->next;
				res = join_text(ms, res, tmp->data);
				ft_remove_if_addr(&lst, tmp->data);
			}
			lst = insert_new_token(ms, lst, res, ptr);
			if (res)
				free(res);
			res = NULL;
		}
		else
			ptr = ptr->next;
	}
	return (lst);
}

t_lst	*plain_text_assemble(t_msh *ms, t_lst *lst)
{
	t_lst	*ptr;
	t_lst	*tmp;
	char	*res;

	ptr = lst;
	res = NULL;
	while (ptr)
	{
		if (ptr && is_all_plain_text(ms, ptr->data))
		{
			while (ptr && is_all_plain_text(ms, ptr->data))
			{
				tmp = ptr;
				ptr = ptr->next;
				res = join_text(ms, res, tmp->data);
				ft_remove_if_addr(&lst, tmp->data);
			}
			lst = insert_new_token(ms, lst, res, ptr);
			if (res && *res != '\0')
				free(res);
			res = NULL;
		}
		else
			ptr = ptr->next;
	}
	return (lst);
}*/

t_lst	*ft_lexer(t_msh *ms)
{
	t_lst *lst;

	lst = ft_token(ms);
	lst = quote_assemble(ms, lst);
	lst = plain_text_assemble(ms, lst);
	return (lst);
}

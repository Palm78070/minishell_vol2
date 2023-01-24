#include "minishell.h"

int	dollar_sign(char *s)
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

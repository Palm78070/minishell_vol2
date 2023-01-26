#include "minishell.h"

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
		if (ptr && quote_joinable(ms, ptr->data))
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
}

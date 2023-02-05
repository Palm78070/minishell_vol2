#include "minishell.h"

int	is_blank_quote(char *s)
{
	int	i;

	i = 0;
	if (s == NULL || s[i] == '\0')
		return (0);
	while (s[i])
	{
		if (!is_quote(s[i++]))
			return (0);
	}
	return (1);
}

int	still_have_quote(char *s)
{
	int	i;

	if (s == NULL)
		return (0);
	i = 1;
	while (s[i])
	{
		if (is_metachar(check_state(s, i++)))
			return (0);
	}
	i = 0;
	while (s[i])
	{
		if (s[i++] == '$')
			return (0);
	}
	i = 0;
	while (s[i])
	{
		if (is_quote(s[i++]))
			return (1);
	}
	return (0);
}

char	*remove_quote(char *old)
{
	char	*res;
	char	quote;
	int	i;

	res = NULL;
	i = 0;
	quote = 0;
	while (old && old[i])
	{
		if (is_quote(old[i]))
		{
			quote = old[i];
			res = check_include_quote(res, old, &i);
			if (old[i] && is_quote(old[i]))
				++i;
			while (old[i] && old[i] != quote)
				res = ft_insert_char(res, old[i++]);
			if (old[i])
				++i;
		}
		else
			res = ft_insert_char(res, old[i++]);
	}
	free(old);
	return (res);
}

t_lst	*handle_quote(t_lst *lst)
{
	t_lst	*ptr;

	ptr = lst;
	while (ptr)
	{
		if (ptr->data && is_blank_quote(ptr->data))
		{
			ft_remove_if_addr(&lst, ptr->data);
			ptr = lst;
		}
		else
			ptr = ptr->next;
	}
	ptr = lst;
	while (ptr)
	{
		while (still_have_quote(ptr->data))
			ptr->data = remove_quote(ptr->data);
		ptr = ptr->next;
	}
	return (lst);
    }

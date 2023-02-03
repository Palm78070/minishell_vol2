#include "minishell.h"

void    init_redirect(t_msh *ms)
{
	int i;

	i = 0;
	while (i < ms->parse.red_size)
	{
		ms->io_red[i].in = -1;
		ms->io_red[i].out = -1;
		ms->io_red[i].heredoc = -1;
		ms->io_red[i].append = -1;
		++i;
	}
}

int	is_redirect(t_msh *ms, t_lst *lst)
{
	if (!list_ok(&lst))
		return (0);
	ms->state = check_state(lst->data, 0);
	if (ms->state == REDIRECT_I || ms->state == REDIRECT_O
			|| ms->state == HEREDOC || ms->state == APPEND)
		return (ms->state);
	return (0);
}

int	is_all_space(char *s)
{
	int i;

	i = 0;
	if (s == NULL || *s == '\0')
		return (0);
	while (s[i])
	{
		if (!ft_isspace(s[i++]))
			return (0);
	}
	return (1);
}

char    *ft_filename(t_lst **lst)
{
	t_lst   *ptr;

	ptr = *lst;
	while (ptr && is_all_space(ptr->data))
	{
		printf("ptr->data %s\n", ptr->data);
		ptr = ptr->next;
	}
	if (ptr)
	{
		printf("filename is %s\n", ptr->data);
		return (ptr->data);
	}
	return (NULL);
}

void	handle_redirect(t_msh *ms, t_lst **lst)
{
	int flag;
	int i;
	char    *filename;

	flag = is_redirect(ms, *lst);
	filename = NULL;
	i = 0;
	while (flag)
	{
		remove_head_node(lst);
		while (list_ok(lst) && is_all_space((*lst)->data))
			remove_head_node(lst);
		if (flag == REDIRECT_O)
		{
			ms->io_red[i].out = open((*lst)->data, O_CREAT|O_RDWR, 0644);
			printf("out[%i] is %i\n", i, ms->io_red[i].out);
		}
		else if (flag == REDIRECT_I)
		{
			ms->io_red[i].in = open((*lst)->data, O_CREAT|O_RDWR, 0644);
			printf("in[%i] is %i\n", i, ms->io_red[i].in);
		}
		else if (flag == HEREDOC)
		{
			if (!list_ok(lst))
				read_heredoc(ms, i, NULL);
			else
				read_heredoc(ms, i, (*lst)->data);
		}
		else if (flag == APPEND)
		{
			ms->io_red[i].append = open((*lst)->data, O_CREAT|O_RDWR, 0644);
			printf("append[%i] is %i\n", i, ms->io_red[i].append);
		}
		remove_head_node(lst);
		flag = is_redirect(ms, *lst);
		++i;
	}
}

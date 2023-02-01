#include "minishell.h"

void    init_redirect(t_msh *ms)
{
    ms->io_red.in = -1;
    ms->io_red.out = -1;
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

int is_all_space(char *s)
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
    char    *filename;

    flag = is_redirect(ms, *lst);
    filename = NULL;
	while (flag)
	{
		remove_head_node(lst);
        while (is_all_space((*lst)->data))
            remove_head_node(lst);
		printf("filename %s\n", (*lst)->data);
        if (flag == REDIRECT_O)
        {
            ms->io_red.out = open((*lst)->data, O_CREAT, 0644);
            printf("out is %i\n", ms->io_red.out);
        }
        else if (flag == REDIRECT_I)
        {
            ms->io_red.in = open((*lst)->data, O_CREAT, 0644);
            printf("in is %i\n", ms->io_red.in);
        }
		remove_head_node(lst);
        flag = is_redirect(ms, *lst);
	}
}
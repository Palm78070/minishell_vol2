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

void	handle_redirect(t_msh *ms, t_lst **lst)
{
    int flag;

    flag = is_redirect(ms, *lst);
	while (flag)
	{
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
#include "minishell.h"

int is_env_var(char *s)
{
    int i;

    i = 0;
    while (s[i] && s[i] != '$')
        ++i;
    if (s[i] == '$')
        return (1);
    return (0);
}

void    parse_red_out(t_msh *ms, t_lst **lst, int i)
{
    if (is_env_var((*lst)->data))
    {
        ms->io_red[i].out = (*lst)->data;
        printf("out is %s\n", (*lst)->data);
    }
    else
        ms->io_red[i].fd_out = open((*lst)->data, O_CREAT|O_RDWR, 0644);
	printf("out[%i] is %i\n", i, ms->io_red[i].fd_out);
}
void    parse_red_in(t_msh *ms, t_lst **lst, int i)
{
    ms->io_red[i].fd_in = open((*lst)->data, O_CREAT|O_RDWR, 0644);
	printf("in[%i] is %i\n", i, ms->io_red[i].fd_in);
}
void    parse_heredoc(t_msh *ms, t_lst **lst, int i)
{
    if (!list_ok(lst))
	    read_heredoc(ms, i, NULL);
	else
        read_heredoc(ms, i, (*lst)->data);
}
void    parse_append(t_msh *ms, t_lst **lst, int i)
{
    ms->io_red[i].fd_append = open((*lst)->data, O_CREAT|O_RDWR, 0644);
	printf("append[%i] is %i\n", i, ms->io_red[i].fd_append);
}
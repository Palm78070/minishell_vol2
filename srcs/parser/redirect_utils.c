#include "minishell.h"

int	is_env_var(char *s)
{
	int i;

	i = 0;
	while (s[i] && s[i] != '$')
		++i;
	if (s[i] == '$')
		return (1);
	return (0);
}

void	parse_red_out(t_msh *ms, t_lst **lst, int i)
{
	if (!list_ok(lst))
		return ;
	if (is_env_var((*lst)->data))
	{
		ms->io_red[i].out = ft_strdup((*lst)->data);
		printf("out is %s\n", ms->io_red[i].out);
	}
	else
		ms->io_red[i].fd_out = open((*lst)->data, O_CREAT|O_RDWR, 0644);
	printf("fd out[%i] is %i\n", i, ms->io_red[i].fd_out);
}
void	parse_red_in(t_msh *ms, t_lst **lst, int i)
{
	ms->io_red[i].in = ft_strdup((*lst)->data);
	printf("in is %s\n", (*lst)->data);
	printf("fd in[%i] is %i\n", i, ms->io_red[i].fd_in);
}

void	parse_heredoc(t_msh *ms, t_lst **lst, int i)
{
	if (list_ok(lst))
		ms->io_red[i].heredoc = ft_strdup((*lst)->data); 
	printf("heredoc delim[%i] is %s\n", i, ms->io_red[i].heredoc);	
}

void	parse_append(t_msh *ms, t_lst **lst, int i)
{
	if (is_env_var((*lst)->data))
	{
		ms->io_red[i].append = (*lst)->data;
		printf("append is %s\n", ms->io_red[i].append);
	}
	else
		ms->io_red[i].fd_append = open((*lst)->data, O_CREAT|O_RDWR, 0644);
	printf("append[%i] is %i\n", i, ms->io_red[i].fd_append);
}

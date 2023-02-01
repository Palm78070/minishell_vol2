#include "minishell.h"

void    ft_parsing(t_msh *ms, t_lst **lst)
{
    create_command_tab(ms, lst);
	print_arg(ms);
	free_cmd_arg(ms);
}
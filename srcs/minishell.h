/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 16:08:37 by rthammat          #+#    #+#             */
/*   Updated: 2023/01/30 23:57:09 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define LLONG_MAX 9223372036854775807

# include <stdio.h>
# include "libft.h"
# include "get_next_line.h"
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
//# include "/usr/local/opt/readline/include/readline"

enum	e_state
{
	SP = ' ',
	S_QUOTE = '\'',
	D_QUOTE = '\"',
	PIPE = '|',
	REDIRECT_I = '<',
	REDIRECT_O = '>',
	HEREDOC = 8,
	APPEND = 9,
	AND_IF = 10,
	OR_IF = 11,
};

typedef struct s_lst
{
	char			*data;
	struct s_lst	*next;
}	t_lst;

typedef struct s_parse
{
	int	cmd_size;
	int	arg_size;
}	t_parse;

typedef struct s_cmd
{
	char	*arg;
}	t_cmd;

typedef struct s_red
{
	int	in;
	int	out;
}	t_red;

typedef struct s_msh
{
	t_cmd	**s_cmd;
	t_parse	parse;
	t_red	io_red;
	char				*line;
	struct sigaction	sa;
	int					state;
}	t_msh;

void	ft_handler(int signum);
//error.c
int	check_error_ok(char *s);
//token.c
t_lst	*token_space(t_msh *ms, t_lst *lst, int *index);
t_lst	*token_pipe(t_msh *ms, t_lst *lst, int *index);
t_lst	*token_redirect(t_msh *ms, t_lst *lst, int *index);
t_lst	*token_double_sign(t_msh *ms, t_lst *lst, int *index);
t_lst	*ft_token(t_msh *ms);
//lexer_utils.c
char	*trim_head(char *s, int delim_indx);
int		check_state(char *s, int i);
t_lst	*insert_str(t_msh *ms, t_lst *lst, int i);
//quote.c
int	is_quote(char c);
void	check_quote(char *line, int *indx);
char	*ft_insert_char(char *old, char c);
char	*remove_quote(char *old);
//lexer.c
t_lst	*ft_lexer(t_msh *ms);
//parsing_utils.c
int	count_simple_cmd(t_msh *ms, t_lst *lst);
int	count_arg_size(t_msh *ms, t_lst *lst);
t_cmd	*insert_args(t_msh *ms, t_lst **lst);
void	print_arg(t_msh *ms);
void	create_command_tab(t_msh *ms, t_lst **lst);
//parsing.c
void    ft_parsing(t_msh *ms, t_lst **lst);
//redirect.c
void	init_redirect(t_msh *ms);
int	is_redirect(t_msh *ms, t_lst *lst);
void	handle_redirect(t_msh *ms, t_lst **lst);
//linked_list.c
void	print_list(t_lst *lst);
t_lst	*create_node(char *s);
t_lst	*insert_end(t_lst *lst, char *s);
void	remove_head_node(t_lst **lst);
int		list_ok(t_lst **lst);
void	ft_remove_if_addr(t_lst **lst, char *data);
//clear.c
void	free_list(t_lst *lst);
void	ft_clear(t_msh *ms);
void	ft_error(char *s, t_msh *ms);
void	free_cmd_arg(t_msh *ms);
//readline.c
void	rl_get(t_msh *ms);
int		is_exit(char *s);
#endif

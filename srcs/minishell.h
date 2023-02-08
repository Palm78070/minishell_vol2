/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 16:08:37 by rthammat          #+#    #+#             */
/*   Updated: 2023/02/08 13:59:07 by rthammat         ###   ########.fr       */
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
	int	red_size;
}	t_parse;

typedef struct s_cmd
{
	char	*arg;
}	t_cmd;

typedef struct s_red
{
	int	fd_in;
	int	fd_out;
	int	fd_append;
	char	*in;
	char	*out;
	char	*heredoc;
	char	*append;
}	t_red;

typedef struct s_msh
{
	t_cmd	**s_cmd;
	t_parse	parse;
	t_red	*io_red;
	char				*line;
	char				*line_hd;
	struct sigaction	sa;
	int					state;
}	t_msh;

void	ft_handler(int signum);
//error.c
int	quote_error_ok(char *s, char *quote);
int	pipe_error_ok(char *s);
int	double_arrow_error_ok(char *s, char c, int i);
int	is_not_file(char *s, int i);
int	arrow_error_ok(char *s, char *c, int *i);
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
char	*ft_insert_char(char *old, char c);
//quote.c
int	is_quote(char c);
int	run_from_quote(char *s, int i);
void	check_quote(char *line, int *indx);
char	*remove_quote(char *old);
char	*check_include_quote(char *res, char *old, int *indx);
//remove_quote.c
int	is_blank_quote(char *s);
int	still_have_quote(char *s);
char	*remove_quote(char *old);
t_lst	*handle_quote(t_lst *lst);
//lexer.c
int	is_metachar(int i);
t_lst	*ft_lexer(t_msh *ms);
//parsing_utils.c
int	count_simple_cmd(t_msh *ms, t_lst *lst);
int	count_arg_size(t_msh *ms, t_lst *lst);
t_cmd	*insert_args(t_msh *ms, t_lst **lst);
void	print_arg(t_msh *ms);
void	create_command_tab(t_msh *ms, t_lst **lst);
//parsing.c
void    ft_parsing(t_msh *ms, t_lst **lst);
//redirect_utils.c
int	is_env_var(char *s);
void    parse_red_out(t_msh *ms, t_lst **lst, int i);
void    parse_red_in(t_msh *ms, t_lst **lst, int i);
void	parse_heredoc(t_msh *ms, t_lst **lst, int i);
void    parse_append(t_msh *ms, t_lst **lst, int i);
//redirect.c
void	init_redirect(t_msh *ms);
int	is_redirect(t_msh *ms, t_lst *lst);
int is_all_space(char *s);
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
void	read_heredoc(t_msh *ms, int fd, char *delim);
#endif

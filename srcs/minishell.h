/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 16:08:37 by rthammat          #+#    #+#             */
/*   Updated: 2023/01/25 03:28:59 by rath             ###   ########.fr       */
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
	OR_IF = 11
};

typedef struct s_lst
{
	char			*data;
	struct s_lst	*next;
}	t_lst;

typedef struct s_msh
{
	char				*line;
	struct sigaction	sa;
	int					state;
}	t_msh;

void	ft_handler(int signum);
//token.c
t_lst	*token_quote(t_msh *ms, t_lst *lst, int *index);
t_lst	*token_space(t_msh *ms, t_lst *lst, int *index);
t_lst	*token_pipe(t_msh *ms, t_lst *lst, int *index);
t_lst	*token_redirect(t_msh *ms, t_lst *lst, int *index);
t_lst	*token_double_sign(t_msh *ms, t_lst *lst, int *index);
//token_assemble_utils.c
int	dollar_sign(char *s);
int	quote_joinable(t_msh *ms, char *s);
void	ft_insert_if_addr(t_lst **lst, char *cmp, char *data);
t_lst	*insert_before_target(t_lst *lst, char *cmp, char *data);
int	is_all_plain_text(t_msh *ms, char *s);
//token_assemble
void	ft_remove_if_addr(t_lst **lst, char *data);
char	*join_text(t_msh *ms, char *res_text, char *data);
t_lst	*insert_new_token(t_msh *ms, t_lst *lst, char *res, t_lst *ptr);
t_lst	*quote_assemble(t_msh *ms, t_lst *lst);
t_lst	*plain_text_assemble(t_msh *ms, t_lst *lst);
//lexer_utils.c
char	*trim_head(char *s, int delim_indx);
int		check_state(char *s, int i);
t_lst	*insert_str(t_msh *ms, t_lst *lst, int i);
//lexer.c
t_lst	*ft_token(t_msh *ms);
t_lst	*ft_lexer(t_msh *ms);
//linked_list.c
void	free_list(t_lst *lst);
void	print_list(t_lst *lst);
t_lst	*create_node(char *s);
t_lst	*insert_end(t_lst *lst, char *s);
//clear.c
void	ft_clear(t_msh *ms);
void	ft_error(char *s, t_msh *ms);
//readline.c
void	rl_get(t_msh *ms);
int		is_exit(char *s);
#endif

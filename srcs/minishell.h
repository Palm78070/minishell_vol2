/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 16:08:37 by rthammat          #+#    #+#             */
/*   Updated: 2023/01/27 21:52:44 by rthammat         ###   ########.fr       */
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
	char	*dummy;
	int	exit;
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
void	check_quote(char *line, int *indx);
char	*ft_insert_char(char *old, char c);
char	*include_quote(char *res, char *old, int *indx);
char	*remove_quote(char *old);
//lexer.c
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

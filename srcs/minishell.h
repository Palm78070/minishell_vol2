/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 16:08:37 by rthammat          #+#    #+#             */
/*   Updated: 2023/03/01 15:02:00 by psutanth         ###   ########.fr       */
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
# include <termios.h>
# include <termcap.h>
# include <sys/wait.h>
# include <errno.h>

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

typedef struct s_red_out
{
	t_lst	*filename;
	int		fd_out;
	int		append;
	int		output;
}	t_redout;

typedef struct s_red_in
{
	t_lst	*filename;
	int		fd_in;
	int		output;
}	t_redin;

typedef struct s_heredoc
{
	t_lst	*delim;
	int		output;
	int		pipe[2];
}	t_heredoc;

typedef struct s_msh
{
	struct sigaction	sa;
	struct sigaction	sa_child;
	t_parse				parse;
	t_redout			*redout;
	t_redin				*redin;
	t_heredoc			*heredoc;
	int					state;
	char				*line;
	char				*line_hd;
	char				***cmd_tb;
	int					should_exit;
	int					estatus;
}	t_msh;

extern t_msh	*g_ms;

//signal.c
struct sigaction	init_sa(void (*ft_handler)(int));
//check_error_utils.c
int					quote_error_ok(char *s, char *quote);
int					pipe_error_ok(char *s, int is_ok);
int					double_arrow_error_ok(char *s, char c, int i);
int					arrow_error_ok(char *s, char *c, int *i);
//check_error.c
int					is_arrow(char c);
int					is_not_file(char *s, int i);
int					check_error_ok(char *s);
//token.c
t_lst				*token_space(t_msh *ms, t_lst *lst, int *index);
t_lst				*token_pipe(t_msh *ms, t_lst *lst, int *index);
t_lst				*token_redirect(t_msh *ms, t_lst *lst, int *index);
t_lst				*token_double_sign(t_msh *ms, t_lst *lst, int *index);
t_lst				*ft_token(t_msh *ms);
//lexer_utils.c
char				*trim_head(char *s, int delim_indx);
int					check_state(char *s, int i);
t_lst				*insert_str(t_msh *ms, t_lst *lst, int i);
char				*ft_insert_char(char *old, char c);
//quote.c
int					is_quote(char c);
int					run_from_quote(char *s, int i);
void				check_quote(char *line, int *indx);
char				*remove_quote(char *old);
char				*check_include_quote(char *res, char *old, int *indx);
//remove_quote.c
int					is_blank_quote(char *s);
//int		still_have_quote(char *s);
char				*remove_quote(char *old);
//t_lst	*handle_quote(t_lst *lst);
//lexer.c
int					is_metachar(int i);
t_lst				*ft_lexer(t_msh *ms);
//parsing_utils.c
int					count_simple_cmd(t_msh *ms, t_lst *lst);
int					count_arg_size(t_msh *ms, t_lst *lst);
char				**insert_args(t_msh *ms, t_lst **lst, int i);
void				print_command_tab(t_msh *ms);
void				create_command_tab(t_msh *ms, t_lst **lst);
//parsing.c
int					ft_parsing(t_msh *ms, t_lst **lst, char **envp);
//redirect_utils.c
int					is_env_var(char *s);
void				parse_red_out(t_msh *ms, t_lst **lst, int i);
void				parse_red_in(t_msh *ms, t_lst **lst, int i);
void				parse_heredoc(t_msh *ms, t_lst **lst, int i);
void				parse_append(t_msh *ms, t_lst **lst, int i);
//redirect.c
void				init_redirect(t_msh *ms);
int					is_redirect(t_msh *ms, t_lst *lst);
int					is_all_space(char *s);
void				handle_redirect(t_msh *ms, t_lst **lst, int i);
//linked_list.c
void				print_list(t_lst *lst);
t_lst				*create_node(char *s);
t_lst				*insert_end(t_lst *lst, char *s);
void				remove_head_node(t_lst **lst);			
int					list_ok(t_lst **lst);
void				ft_remove_if_addr(t_lst **lst, char *data);
//clear.c
void				free_list(t_lst *lst);
void				ft_clear(t_msh *ms);
void				ft_error(char *s, t_msh *ms);
void				free_cmd_tab(t_msh *ms);
//clear_redirect.c
void				clear_filename(char *s);
void				free_redirect(t_msh *ms);
//readline.c
void				rl_get(t_msh *ms);
int					is_exit(char *s);
void				read_heredoc(t_msh *ms, int fd, char *delim);
//signal.c
//struct sigaction	init_sa(void (*ft_handler)(int));
void				ft_handler(int signum);
void				ft_handler_child(int signum);
void				ft_signal(struct sigaction sa);
//expanding.c
int					ft_expand(t_msh *ms, char **envp);
//expand_redirects.c
int					expand_redout(t_redout *redout, int cmdsize, char **envp);
int					expand_redin(t_redin *redin, int cmdsize, char **envp);
//expander_utils.c
char				*get_envp_value(char *key, char **envp);
void				splice_char_array(char ***arr, size_t index);
char				*ft_strjoin_arr(char **arr);
void				free_strarr(char **strs);
//try_expand.c
char				*simple_expand(char *str, char **envp);
char				*try_expand_var(char *arg, char **envp);
//splitting.c
size_t				count_var_splits(char *str);
char				**make_var_splits(char *str);
//executing.c
int					ft_execute(t_msh *ms, char **envp);
//ft_execvpe.c
int					ft_execvpe(char *progname, char **argv, char **envp);
//handle_pipes.c
int					**create_pipes(t_msh *ms);			
void				close_pipes_index(int **pipes, int index);
int					dup2_close(int old_fd, int new_fd);
void				destroy_pipes(int **pipes);
//builtins_1.c
int					builtin_pwd(void);
int					builtin_echo(char **argv);
#endif

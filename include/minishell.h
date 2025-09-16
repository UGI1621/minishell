/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:19:24 by saan              #+#    #+#             */
/*   Updated: 2025/09/16 12:21:22 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#ifndef ECHOCTL
# define ECHOCTL 0001000
#endif

#include "libft.h"
# include <termios.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_cmd_node
{
	struct s_cmd_node	*prev;
	char				*cmd_path;
	char				**argv;
	char				**infile;
	int					in_fd;
	char				**outfile;
	char				**out_sig;
	int					out_fd;
	int					is_use_heredoc;
	int					heredoc_fd;
	int					pipe[2];
	struct s_cmd_node	*next;
}	t_cmd_node;

typedef struct s_cmd_list
{
	t_cmd_node			*head;
	t_cmd_node			*tail;
}	t_cmd_list;

typedef struct s_lexer_node
{
	struct s_lexer_node	*prev;
	char	*str;
	struct s_lexer_node *next;
} t_lexer_node;

typedef struct s_lexer_list
{
	t_lexer_node	*head;
	t_lexer_node	*tail;
} t_lexer_list;

typedef struct s_env_node
{
	struct s_env_node *prev;
	char *key;
	char *val;
	struct s_env_node *next;
} t_env_node;

typedef struct s_env_list
{
	t_env_node *head;
	int	size;
	t_env_node *tail;
} t_env_list;

typedef struct s_sigs
{
	int	heredoc_sigint;
	unsigned char	exit_code;
}	t_sigs;


//								execve
// exe_cmds.c
void	process_cmd_exe(t_cmd_list *list, t_env_list *my_env);

// handle_error.c
void	exit_with_perror(char *str);
void	write_open_error(char *name);
void	write_access_error(char *name, int err);
void	write_cmd_nf(char *name);

// redirection.c
int	open_infiles(char **files);
int	open_outfiles(char **files, char **sigs);
void	set_node_fds(t_cmd_node *node);

// cmd_path.c
void	check_and_set_argv(t_cmd_node *node, t_env_list *my_env);

// set_builtin.c
int	is_builtin(t_cmd_node *node);
int	do_builtin(t_cmd_node *node, int is_p, t_env_list *my_env);
void	set_iofds(int s_stdin, int s_stdout);

// util_builtin.c
int	b_open_infiles(char **files);
int	b_open_outfiles(char **files, char **sigs);

// handle_status.c
void	set_status(int status);
void	check_status(int status);
void	set_heredoc_status(int status);


//								built-in
int	ft_echo(t_cmd_node *node, int save_stdin, int save_stdout);
int	ft_pwd(t_cmd_node *node, int save_stdin, int save_stdout);
int	ft_env(t_cmd_node *node, t_env_list *my_env, int save_stdin, int save_stdout);
int	ft_exit(t_cmd_node *node, int save_stdin, int save_stdout);
int	ft_export(t_cmd_node *node, int save_stdin, int save_stdout, t_env_list *my_env);
void	print_invalid_export(char *arg, int *flag);
int	ft_unset(t_cmd_node *node, int save_stdin, int save_stdout, t_env_list *my_env);
int	ft_cd(t_cmd_node *node, int save_stdin, int save_stdout, t_env_list *my_env);

char	*parsing_path(char *str, t_env_list *my_env);
void	update_pwds(char *cur, char *old, t_env_list *my_env);
int	print_error_path(char *path, int save_stdin, int save_stdout);

// 								heredoc
// heredoc.c
void	heredoc_proc(char *delimiter, int heredoc_fd, int is_quote, t_env_list *my_env);


// 								cmd_list
// listing_cmd.c
t_cmd_list	*listing_cmd(t_lexer_list *list, t_env_list *my_env);

// quotting.c
char	*extending(char *s, t_env_list *my_env);
char	*cal_quotes(char *line, int	is_extend, t_env_list *my_env);

// quotting_util.c
char	*get_quotes_env_key(char *line, int *idx);
char	*get_extra_sign(char *str, char *line, int *idx);

// listing_util.c
int	is_redir_node(char *s);
int	is_heredoc_node(char *s);
char	*ft_strjoin_af(char *s1, char *s2);

// cmd_free.c
void	free_cmd_list(t_cmd_list *list);
void	free_cmd_field(t_cmd_node *node);
void	open_error_proc(t_cmd_list *list);

// setting_fds.c
void		set_in_fd(t_cmd_node *c_node, t_lexer_node **l_node);
void		set_out_fd(t_cmd_node *c_node, t_lexer_node **l_node, int is_append);
void	set_heredoc_fd(t_cmd_node *c_node, t_lexer_node **l_node, t_env_list *my_env);


//								cmd_quoting

// extending_lexer_list.c
void	extending_lexer_list(t_lexer_list **list, t_env_list *my_env);

// env_extend.c
char	*extending_env(char *str, t_env_list *my_env);

// extending_util.c
int	is_expandable(char *str);
char	*extend_res(char *s, t_env_list *my_env);
char	*no_extend_res(char *s);

// quoting_lexer_list.c
void	quotting_lexer_list(t_lexer_list **list);
char	*remove_quotes(char *str);

// 								siganl
// sig_handler.c
// void	init_sigs(void);
// void	s_sigint_handler(int signum);

// set_signal.c
void	set_sigs(void);
void	set_sigs_ign(void);
void	set_sigs_dfl(void);
void	set_sigs_heredoc(void);

// sig_handler.c
void	sigint_handler(int signum);
void	sigint_handler_heredoc(int signum);

// set_sig_handler.c
void	set_sigint_handler(void);
void	set_sigquit_handler(void);
void	set_sigint_handler_heredoc(void);

// set_sig_ign.c
void	set_sigint_ign(void);
void	set_sigquit_ign(void);

// set_sig_dfl.c
void	set_sigint_dfl(void);
void	set_sigquit_dfl(void);

// set_terminal.c
void	set_techo_on(void);
void	set_techo_off(void);


// 								lexing
// lexing_list.c
void	add_lexer_node(t_lexer_list *list, char *str);
t_lexer_list	*ft_lexing(char *line, t_env_list *my_env);
void	free_lexer_list(t_lexer_list *list);

// lexing_proc.c
int	ft_lexing_proc(t_lexer_list *res, char *line, int *i);

// get_word.c
char	*append_char(char *str, char c);
int	get_word_redir(t_lexer_list *res, char *line, int *idx, char *sig);


//								env
// envp_to_env.c
void	envp_to_env(t_env_list **my_env, char **env);
void	init_env_list(t_env_list **my_env);
void	init_env_node(t_env_node *node, char *env);
void	add_env_node(t_env_list *list, t_env_node *node);
void	print_env_list(t_env_list *list);			// <<< testcode

// env_to_envp.c
char	**env_to_envp(t_env_list *my_env);

// env_util.c
void	del_env(char *key, t_env_list *my_env);
char	*get_env(char *key, t_env_list *my_env);
void	set_env(char *key, char *val, t_env_list *my_env);
void	check_cmd_env(t_env_list *my_env);			// <<< testcode
void	env_free(t_env_list *my_env);


// 								root
// util.c
int	is_wspace(char c);
int	is_quote(char c);
int	is_cutsign(char c);
void	free_2ptr(char **ptr);
int	invalid_token(t_lexer_list *res, char c);

// initialize.c
void	init_lexer_list(t_lexer_list **list);
void	init_cmd_list(t_cmd_list **list);
void	init_cmd_node(t_cmd_node **node);

// valid.c
int	is_invalid_line(char *line);
int	is_invalid_env_naming_rule(char *str);

void	print_lexing_list(t_lexer_list *list);

extern t_sigs g_sigs;

#endif

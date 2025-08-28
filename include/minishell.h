/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:19:24 by saan              #+#    #+#             */
/*   Updated: 2025/08/28 17:54:03 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
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
	// int					heredoc_fd;
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
	int	sigterm;
	int	exit_code;
}	t_sigs;


//								execve
// exe_cmds.c
void	process_cmd_exe(t_cmd_list *list, t_env_list *my_env);

// handle_error.c
void	exit_with_perror(char *str);
void	write_open_error(char *name);
void	write_access_error(char *name);

// redirection.c
int	open_infiles(char **files);
int	open_outfiles(char **files, char **sigs);
void	set_node_fds(t_cmd_node *node);

// cmd_path.c
void	check_and_set_argv(t_cmd_node *node);

// util.c
int	is_builtin(t_cmd_node *node);
void	do_builtin(t_cmd_node *node, int is_p);


//								built-in
void	ft_echo(t_cmd_node *node);
void	ft_pwd(t_cmd_node *node);

// 								heredoc
// heredoc.c
void	heredoc_proc(char *delimiter, int heredoc_fd, int is_quote);


// 								cmd_list
// listing_cmd.c
t_cmd_list	*listing_cmd(t_lexer_list *list);

// quotting.c
char	*cal_quotes(char *line, int	is_heredoc);

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
void		set_out_fd(t_cmd_node *c_node, t_lexer_node **l_node, int is_heredoc);
void	set_heredoc_fd(t_cmd_node *c_node, t_lexer_node **l_node);


// 								siganl
// sa_handler.c
void	s_sigint_handler(int signum);
void	s_sigquit_handler(int signum);


// 								lexing
// lexing_list.c
void	add_lexer_node(t_lexer_list *list, char *str);
t_lexer_list	*ft_lexing(char *line);
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


// 								root
// util.c
int	is_wspace(char c);
int	is_quote(char c);
int	is_cutsign(char c);
void	free_2ptr(char **ptr);
int	invalid_token(t_lexer_list *res, char c);

// initialize.c
void	init_sigs(void);
void	init_lexer_list(t_lexer_list **list);
void	init_cmd_list(t_cmd_list **list);
void	init_cmd_node(t_cmd_node **node, t_cmd_list *list);

// valid.c
int	is_invalid_line(char *line);

extern t_sigs g_sigs;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:19:24 by saan              #+#    #+#             */
/*   Updated: 2025/07/28 17:24:23 by saan             ###   ########.fr       */
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
	char				type;
	char				**cmd_args;
	int					pipe[2];
	struct s_cmd_node	*next;
}	t_cmd_node;

typedef struct s_dllist
{
	t_cmd_node			*head;
	int					size;
	char				**env;
	t_cmd_node			*tail;
}	t_dllist;

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

typedef struct s_sigs
{
	int	sigterm;
	int	exit_code;
}	t_sigs;

// lexing_list.c
void	add_lexer_node(t_lexer_list *list, char *str);
t_lexer_list	*ft_lexing(char *line);

// lexing_proc.c
void	ft_lexing_proc(t_lexer_list *res, char *line, int *i, int *flag);

// get_word.c
int	flag_0_get_word(t_lexer_list *list, char *line, int *idx, int *flag);

// util.c
int	is_wspace(char c);
int	is_quote(char c);
int	is_cutsign(char c);
char	*ft_join_fa(char *s1, char *s2);
char	*ft_join_fs1(char *s1, char *s2);

// initialize.c
void	init_sigs(void);
t_lexer_list	*init_lexer_list(t_lexer_list *list);

// valid.c
int	is_invalid_line(char *line);

// sa_handler.c
void	s_sigint_handler(int signum);
void	s_sigquit_handler(int signum);

extern t_sigs g_sigs;
#endif

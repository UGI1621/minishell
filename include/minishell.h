/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:19:24 by saan              #+#    #+#             */
/*   Updated: 2025/07/24 18:14:03 by saan             ###   ########.fr       */
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
	int					fd_input;
	int					fd_output;
	char				**env;
	t_cmd_node			*tail;
}	t_dllist;

typedef struct s_stack
{
	char *stack;
	int	top;
}	t_stack;

typedef struct s_sigs
{
	int	sigterm;
	int	exit_code;
}	t_sigs;


// util.c
int	is_wspace(char c);
int	is_quote(char c);
char	*ft_join_fa(char *s1, char *s2);

// initialize.c
void	init_sigs(void);

// quote.c
int	open_quote(char *line);

// parsing.c
char	*normalize_cmd(char *line);

// sa_handler.c
void	s_sigint_handler(int signum);
void	s_sigquit_handler(int signum);
void	s_sigterm_handler(int signum);

extern t_sigs g_sigs;
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:19:24 by saan              #+#    #+#             */
/*   Updated: 2025/07/15 21:06:44 by saan             ###   ########.fr       */
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

// initialize.c
void	init_sigs(void);

// sa_handler.c
void	sa_sigint_handler(int signum);

#endif

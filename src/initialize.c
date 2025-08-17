/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:35:17 by saan              #+#    #+#             */
/*   Updated: 2025/08/17 14:18:59 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_sigs(void)
{
	if (signal(SIGINT, s_sigint_handler) == SIG_ERR)
	{
		perror("signal SIGINT");
		exit(EXIT_FAILURE);
	}
	if (signal(SIGQUIT, s_sigquit_handler) == SIG_ERR)
	{
		perror("signal SIGQUIT");
		exit(EXIT_FAILURE);
	}
}

void	init_lexer_list(t_lexer_list **list)
{
	*list = (t_lexer_list *)ft_calloc(1, sizeof(t_lexer_list));
	(*list)->head = NULL;
	(*list)->tail = NULL;
}

void	init_cmd_list(t_dllist **list)
{
	*list = (t_dllist *)ft_calloc(1, sizeof(t_dllist));
	(*list)->head = NULL;
	(*list)->heredoc_fd = -1;
	(*list)->tail = NULL;
}

void	init_cmd_node(t_cmd_node **node, t_dllist *list)
{
	*node = (t_cmd_node *)ft_calloc(1, sizeof(t_cmd_node));
	(*node)->prev = NULL;
	(*node)->argv = (char **)ft_calloc(1, sizeof(char *));
	(*node)->argv[0] = NULL;
	(*node)->infile = (char **)ft_calloc(1, sizeof(char *));
	(*node)->infile[0] = NULL;
	(*node)->in_fd = STDIN_FILENO;
	(*node)->outfile = (char **)ft_calloc(1, sizeof(char *));
	(*node)->outfile[0] = NULL;
	(*node)->out_sig = (char **)ft_calloc(1, sizeof(char *));
	(*node)->out_sig[0] = NULL;
	(*node)->out_fd = STDOUT_FILENO;
	(*node)->is_use_heredoc = 0;
	(*node)->heredoc_fd = &list->heredoc_fd;
	(*node)->pipe[0] = -1;
	(*node)->pipe[1] = -1;
	(*node)->next = NULL;
}

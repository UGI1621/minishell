/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:35:17 by saan              #+#    #+#             */
/*   Updated: 2025/09/17 12:36:45 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_lexer_list(t_lexer_list **list)
{
	*list = (t_lexer_list *)ft_calloc(1, sizeof(t_lexer_list));
	(*list)->head = NULL;
	(*list)->tail = NULL;
}

void	init_cmd_list(t_cmd_list **list)
{
	*list = (t_cmd_list *)ft_calloc(1, sizeof(t_cmd_list));
	(*list)->head = NULL;
	(*list)->tail = NULL;
}

void	init_cmd_node(t_cmd_node **node)
{
	*node = (t_cmd_node *)ft_calloc(1, sizeof(t_cmd_node));
	(*node)->prev = NULL;
	(*node)->cmd_path = NULL;
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
	(*node)->heredoc_fd = -1;
	(*node)->pipe[0] = -1;
	(*node)->pipe[1] = -1;
	(*node)->next = NULL;
}

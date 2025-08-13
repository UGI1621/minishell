/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:02:05 by saan              #+#    #+#             */
/*   Updated: 2025/08/13 17:26:18 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_field(t_cmd_node *node)
{
	if (node->argv)
		free_2ptr(node->argv);
	if (node->infile)
		free(node->infile);
	if (node->in_fd != -1)
		close(node->in_fd);
	if (node->outfile)
		free(node->outfile);
	if (node->out_fd != -1)
		close(node->out_fd);
	// if (node->heredoc_delim)
	// 	free(node->heredoc_delim);
}

void	free_cmd_list(t_dllist *list)
{
	t_cmd_node	*node;
	t_cmd_node	*temp;

	if (list->heredoc_fd != -1)
		close(list->heredoc_fd);
	// unlink("heredoc_temp");
	node = list->head;
	while(node)
	{
		free_cmd_field(node);
		temp = node;
		node = node->next;
		free(temp);
	}
	free(list);
}

void	open_error_proc(t_dllist *list)
{
	t_cmd_node	*node;
	t_cmd_node	*temp;

	node = list->tail;
	while (node)
	{
		free_cmd_field(node);
		temp = node;
		node = node->prev;
		list->tail = node;
		free(temp);
	}
	list->head = NULL;
	list->tail = NULL;
}

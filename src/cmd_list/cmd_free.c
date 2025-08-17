/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:02:05 by saan              #+#    #+#             */
/*   Updated: 2025/08/17 08:51:50 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_field(t_cmd_node *node)
{
	if (node->argv)
		free_2ptr(node->argv);
	if (node->infile)
		free_2ptr(node->infile);
	if (node->outfile)
		free_2ptr(node->outfile);
	if (node->out_sig)
		free_2ptr(node->out_sig);
}

void	free_cmd_list(t_dllist *list)
{
	t_cmd_node	*node;
	t_cmd_node	*temp;

	if (list->heredoc_fd != -1)
		close(list->heredoc_fd);
	unlink("heredoc_temp");
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

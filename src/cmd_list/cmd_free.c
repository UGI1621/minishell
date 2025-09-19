/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:02:05 by saan              #+#    #+#             */
/*   Updated: 2025/09/19 20:50:10 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_field(t_cmd_node *node)
{
	if (node->cmd_path)
		free(node->cmd_path);
	if (node->argv)
		free_2ptr(node->argv);
	if (node->infile)
		free_2ptr(node->infile);
	if (node->outfile)
		free_2ptr(node->outfile);
	if (node->out_sig)
		free_2ptr(node->out_sig);
	if (node->pipe[0] != -1)
		close(node->pipe[0]);
	if (node->pipe[1] != -1)
		close(node->pipe[1]);
}

void	free_cmd_list(t_cmd_list *list)
{
	t_cmd_node	*node;
	t_cmd_node	*temp;

	if (!list)
		return ;
	node = list->head;
	if (node && node->heredoc_fd != -1)
		close(node->heredoc_fd);
	unlink("heredoc_temp");
	while (node)
	{
		free_cmd_field(node);
		temp = node;
		node = node->next;
		free(temp);
	}
	free(list);
}

void	open_error_proc(t_cmd_list *list)
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

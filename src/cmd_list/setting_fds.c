/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_fds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 11:10:14 by saan              #+#    #+#             */
/*   Updated: 2025/08/13 12:16:14 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		set_in_fd(t_cmd_node *c_node, t_lexer_node **l_node)
{
	if (c_node->infile)
	{
		free(c_node->infile);
		c_node->infile = NULL;
	}
	(*l_node) = (*l_node)->next;
	c_node->infile = cal_quotes(ft_strdup((*l_node)->str), 0);
	c_node->in_fd = open(c_node->infile, O_RDONLY);
	if (c_node->in_fd == -1)
	{
		perror(c_node->infile);
		return (1);
	}
	return (0);
}

int		set_out_fd(t_cmd_node *c_node, t_lexer_node **l_node, int is_append)
{
	if (c_node->outfile)
	{
		free(c_node->outfile);
		c_node->outfile = NULL;
	}
	(*l_node) = (*l_node)->next;
	c_node->outfile = cal_quotes(ft_strdup((*l_node)->str), 0);
	if (is_append)
		c_node->out_fd = open(c_node->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		c_node->out_fd = open(c_node->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (c_node->out_fd == -1)
	{
		perror(c_node->outfile);
		return (1);
	}
	return (0);
}

int	set_heredoc_fd(t_cmd_node *c_node, t_lexer_node **l_node)
{
	(*l_node) = (*l_node)->next;
	c_node->heredoc_delim = cal_quotes(ft_strdup((*l_node)->str), 1);
	if (*c_node->heredoc_fd != -1)
		close(*c_node->heredoc_fd);
	*c_node->heredoc_fd = open("heredoc_temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (0);
}

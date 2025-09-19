/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_fds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 11:10:14 by saan              #+#    #+#             */
/*   Updated: 2025/09/20 02:46:49 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_in_sig(t_cmd_node *c_node, char *sig)
{
	int		len;
	int		i;
	char	**new;

	len = 0;
	while (c_node->in_sig && c_node->in_sig[len])
		len++;
	new = (char **)ft_calloc(len + 2, sizeof(char *));
	i = 0;
	while (c_node->in_sig && c_node->in_sig[i])
	{
		new[i] = ft_strdup(c_node->in_sig[i]);
		++i;
	}
	new[i] = ft_strdup(sig);
	new[i + 1] = NULL;
	free_2ptr(c_node->in_sig);
	c_node->in_sig = new;
}

void	set_in_fd(t_cmd_node *c_node, t_lexer_node **l_node)
{
	int		len;
	int		i;
	char	**new;

	len = 0;
	while (c_node->infile && c_node->infile[len])
		len++;
	new = (char **)ft_calloc(len + 2, sizeof(char *));
	i = 0;
	while (c_node->infile && c_node->infile[i])
	{
		new[i] = ft_strdup(c_node->infile[i]);
		i++;
	}
	(*l_node) = (*l_node)->next;
	new[i] = ft_strdup((*l_node)->str);
	new[i + 1] = NULL;
	set_in_sig(c_node, "<");
	free_2ptr(c_node->infile);
	c_node->infile = new;
}

static void	set_out_sig(t_cmd_node *c_node, int is_append)
{
	int		len;
	int		i;
	char	**new;

	len = 0;
	while (c_node->out_sig && c_node->out_sig[len])
		len++;
	new = (char **)ft_calloc(len + 2, sizeof(char *));
	i = 0;
	while (c_node->out_sig && c_node->out_sig[i])
	{
		new[i] = ft_strdup(c_node->out_sig[i]);
		++i;
	}
	if (is_append)
		new[i] = ft_strdup(">>");
	else
		new[i] = ft_strdup(">");
	new[i + 1] = NULL;
	free_2ptr(c_node->out_sig);
	c_node->out_sig = new;
}

void	set_out_fd(t_cmd_node *c_node, t_lexer_node **l_node, int is_append)
{
	int		len;
	int		i;
	char	**new;

	len = 0;
	while (c_node->outfile && c_node->outfile[len])
		len++;
	new = (char **)ft_calloc(len + 2, sizeof(char *));
	i = 0;
	while (c_node->outfile && c_node->outfile[i])
	{
		new[i] = ft_strdup(c_node->outfile[i]);
		i++;
	}
	(*l_node) = (*l_node)->next;
	new[i] = ft_strdup((*l_node)->str);
	new[i + 1] = NULL;
	set_out_sig(c_node, is_append);
	free_2ptr(c_node->outfile);
	c_node->outfile = new;
}

void	set_heredoc_fd(t_cmd_node *node)
{
	if (node->heredoc_fd != -1)
		close(node->heredoc_fd);
	node->heredoc_fd = open("heredoc_temp", O_WRONLY | O_CREAT | O_TRUNC,
			0644);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listing_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:56:16 by saan              #+#    #+#             */
/*   Updated: 2025/08/13 12:19:31 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir_node(char *s)
{
	if (!ft_strncmp(s, "<", ft_strlen(s)) ||
	!ft_strncmp(s, ">", ft_strlen(s)) || !ft_strncmp(s, ">>", ft_strlen(s)))
		return (1);
	return (0);
}

int	is_heredoc_node(char *s)
{
	if (!ft_strncmp(s, "<<", ft_strlen(s)))
		return (1);
	return (0);
}

char	*ft_strjoin_af(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

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
	if (node->heredoc_delim)
		free(node->heredoc_delim);
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

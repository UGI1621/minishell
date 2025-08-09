/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:19:22 by saan              #+#    #+#             */
/*   Updated: 2025/08/09 19:19:34 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_iofile(t_cmd_node *c_node, t_lexer_node **l_node)
{
	if (!ft_strncmp((*l_node)->str, "<", ft_strlen((*l_node)->str)))
	{
		if (c_node->infile)
			free(c_node->infile);
		*l_node = (*l_node)->next;
		c_node->infile = ft_strdup((*l_node)->str);
	}
	else if(!ft_strncmp((*l_node)->str, ">", ft_strlen((*l_node)->str)))
	{
		if (c_node->outfile)
			free(c_node->outfile);
		*l_node = (*l_node)->next;
		c_node->outfile = ft_strdup((*l_node)->str);
	}
	else if(!ft_strncmp((*l_node)->str, ">>", ft_strlen((*l_node)->str)))
	{
		if (c_node->outfile)
			free(c_node->outfile);
		*l_node = (*l_node)->next;
		c_node->append_out = 1;
		c_node->outfile = ft_strdup((*l_node)->str);
	}
}

void	append_argv(t_cmd_node *c_node, t_lexer_node **l_node)
{
	int	len;
	int	i;
	char	**new;

	len = 0;
	while (c_node->argv && c_node->argv[len])
		len++;
	new = (char **)ft_calloc(len + 2, sizeof(char *));
	i = 0;
	while(c_node->argv && c_node->argv[i])
	{
		new[i] = ft_strdup(c_node->argv[i]);
		i++;
	}
	new[i] = ft_strdup((*l_node)->str);
	new[i + 1] = NULL;
	free_2ptr(c_node->argv);
	c_node->argv = new;
}

void	setting_node(t_cmd_node *c_node, t_lexer_node **l_node)
{
	if (is_heredoc_node((*l_node)->str))
	{
		// heredoc ==> quoting but no extending
		(*l_node) = (*l_node)->next;
		c_node->heredoc_delim = ft_strdup((*l_node)->str);
		return ;
	}
	while (*l_node && ft_strncmp((*l_node)->str, "|", ft_strlen((*l_node)->str)))
	{
		// quoting and extending
		if(is_redir_node((*l_node)->str))
			update_iofile(c_node, l_node);
		else
			append_argv(c_node, l_node);
		*l_node = (*l_node)->next;
	}
}

void	add_cmd_node(t_dllist *list, t_cmd_node *node)
{
	t_cmd_node	*temp;

	if(!list->head && !list->tail)
	{
		list->head = node;
		list->tail = node;
	}
	else if (!list->tail->next)
	{
		list->tail->next = node;
		node->prev = list->tail;
		list->tail = node;
	}
}

t_dllist	*listing_cmd(t_lexer_list *list)
{
	t_dllist	*res;
	t_cmd_node	*c_node;
	t_lexer_node	*l_node;

	init_cmd_list(&res);
	l_node = list->head;
	while (l_node)
	{
		init_cmd_node(&c_node);
		setting_node(c_node, &l_node);
		add_cmd_node(res, c_node);
		if (!l_node)
			break ;
		l_node = l_node->next;
	}
	return (res);
}

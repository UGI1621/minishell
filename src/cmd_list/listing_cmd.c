/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:19:22 by saan              #+#    #+#             */
/*   Updated: 2025/08/13 12:23:55 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	update_iofile(t_cmd_node *c_node, t_lexer_node **l_node)
{
	if (!ft_strncmp((*l_node)->str, "<", ft_strlen((*l_node)->str)))
	{
		if (set_in_fd(c_node, l_node))
			return (1);
	}
	else if(!ft_strncmp((*l_node)->str, ">", ft_strlen((*l_node)->str)))
	{
		if (set_out_fd(c_node, l_node, 0))
			return (1);
	}
	else if(!ft_strncmp((*l_node)->str, ">>", ft_strlen((*l_node)->str)))
	{
		if (set_out_fd(c_node, l_node, 1))
			return (1);
		c_node->append_out = 1;
	}
	return (0);
}

static void	append_argv(t_cmd_node *c_node, t_lexer_node **l_node)
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
		new[i] = cal_quotes(ft_strdup(c_node->argv[i]), 0);
		i++;
	}
	new[i] = cal_quotes(ft_strdup((*l_node)->str), 0);
	new[i + 1] = NULL;
	free_2ptr(c_node->argv);
	c_node->argv = new;
}

static int	setting_node(t_cmd_node *c_node, t_lexer_node **l_node)
{
	while (*l_node && ft_strncmp((*l_node)->str, "|", ft_strlen((*l_node)->str)))
	{
		if(is_redir_node((*l_node)->str))
		{
			if(update_iofile(c_node, l_node))
				return (1);
		}
		else if (is_heredoc_node((*l_node)->str))
		{
			set_heredoc_fd(c_node, l_node);
			break ;
		}
		else
			append_argv(c_node, l_node);
		if ((*l_node)->next && is_heredoc_node((*l_node)->next->str))
			break ;
		*l_node = (*l_node)->next;
		// built-in cmd condition (?)
	}
	return (0);
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
		init_cmd_node(&c_node, res);
		if (setting_node(c_node, &l_node))
		{
			free(c_node);
			while(l_node && ft_strncmp(l_node->str, "|", ft_strlen(l_node->str)))
				l_node = l_node->next;
			l_node = l_node->next;
			continue ;
		}
		add_cmd_node(res, c_node);
		if (!l_node)
			break ;
		l_node = l_node->next;
	}
	return (res);
}

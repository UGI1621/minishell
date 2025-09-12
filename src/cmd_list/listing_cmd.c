/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:19:22 by saan              #+#    #+#             */
/*   Updated: 2025/09/12 11:31:04 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_cmd_node(t_cmd_list *list, t_cmd_node *node)
{
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

static void	update_iofile(t_cmd_node *c_node, t_lexer_node **l_node)
{
	if (!ft_strcmp((*l_node)->str, "<"))
	{
		set_in_fd(c_node, l_node);
		c_node->is_use_heredoc = 0;
	}
	else if(!ft_strcmp((*l_node)->str, ">"))
	{
		set_out_fd(c_node, l_node, 0);
	}
	else if(!ft_strcmp((*l_node)->str, ">>"))
	{
		set_out_fd(c_node, l_node, 1);
	}
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
		new[i] = ft_strdup(c_node->argv[i]);
		i++;
	}
	// new[i] = cal_quotes(ft_strdup((*l_node)->str), 1, my_env);
	new[i] = ft_strdup((*l_node)->str);
	new[i + 1] = NULL;
	free_2ptr(c_node->argv);
	c_node->argv = new;
}

static void	setting_node(t_cmd_node *c_node, t_lexer_node **l_node, t_env_list *my_env)
{
	while (*l_node && ft_strcmp((*l_node)->str, "|"))
	{
		if(is_redir_node((*l_node)->str))
			update_iofile(c_node, l_node);
		else if (is_heredoc_node((*l_node)->str))
			set_heredoc_fd(c_node, l_node, my_env);
		else
			append_argv(c_node, l_node);
		*l_node = (*l_node)->next;
	}
}

t_cmd_list	*listing_cmd(t_lexer_list *list, t_env_list *my_env)
{
	t_cmd_list	*res;
	t_cmd_node	*c_node;
	t_lexer_node	*l_node;

	init_cmd_list(&res);
	l_node = list->head;
	while (l_node)
	{
		init_cmd_node(&c_node);
		setting_node(c_node, &l_node, my_env);
		add_cmd_node(res, c_node);
		if (!l_node)
			break ;
		l_node = l_node->next;
	}
	return (res);
}

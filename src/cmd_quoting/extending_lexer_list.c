/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extending_lexer_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:39:35 by saan              #+#    #+#             */
/*   Updated: 2025/09/17 12:45:38 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	extending_lexer_list(t_lexer_list **list, t_env_list *my_env)
{
	t_lexer_list	*res;
	t_lexer_node	*node;

	init_lexer_list(&res);
	node = (*list)->head;
	while (node)
	{
		if (node->prev && !ft_strcmp(node->prev->str, "<<"))
		{
			add_lexer_node(res, ft_strdup(node->str));
			node = node->next;
			continue ;
		}
		add_lexer_node(res, extending_env(node->str, my_env));
		node = node->next;
	}
	free_lexer_list((*list));
	(*list) = res;
}

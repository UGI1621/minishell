/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 02:22:29 by saan              #+#    #+#             */
/*   Updated: 2025/07/28 20:41:17 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_lexer_node(t_lexer_list *list, char *str)
{
	t_lexer_node	*node;

	if (!*str)
		return ;
	node = (t_lexer_node *)ft_calloc(1, sizeof(t_lexer_node));
	node->str = str;
	if (!list->head && !list->tail)
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

t_lexer_list	*ft_lexing(char *line)
{
	t_lexer_list	*res;
	int				i;
	int				start;
	int				flag;

	i = -1;
	res = init_lexer_list(res);
	flag = 0;
	while(line[++i])
	{
		ft_lexing_proc(res, line, &i, &flag);
	}
	return (res);
}

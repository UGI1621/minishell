/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 02:22:29 by saan              #+#    #+#             */
/*   Updated: 2025/08/13 12:02:19 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_lexer_node(t_lexer_list *list, char *str)
{
	t_lexer_node	*node;

	node = (t_lexer_node *)ft_calloc(1, sizeof(t_lexer_node));
	if (!str || !str[0])
		return ;
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

static int	is_invalid_lexer(t_lexer_list *res)
{
	t_lexer_node	*node;

	node = res->head;
	while (node)
	{
		if (is_cutsign(node->str[0]))
		{
			if (!node->next || is_cutsign(node->next->str[0]))
				return(invalid_token(res, node->str[0]));
		}
		node = node->next;
	}
	return (0);
}

t_lexer_list	*ft_lexing(char *line)
{
	t_lexer_list	*res;
	int				i;

	i = -1;
	init_lexer_list(&res);
	while(line[++i])
	{
		if(ft_lexing_proc(res, line, &i))
		{
			free_lexer_list(res);
			return (NULL);
			break ;
		}
		if (!line[i])
			break ;
	}
	if (is_invalid_lexer(res))
	{
		free_lexer_list(res);
		return (NULL);
	}
	return (res);
}

void	free_lexer_list(t_lexer_list *list)
{
	t_lexer_node	*node;
	t_lexer_node	*temp;

	node = list->head;
	while(node)
	{
		temp = node->next;
		free(node->str);
		free(node);
		node = temp;
	}
	free(list);
}

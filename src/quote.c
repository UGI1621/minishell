/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:39:53 by saan              #+#    #+#             */
/*   Updated: 2025/07/24 13:59:53 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_pop(t_stack *quote)
{
	quote->stack[quote->top] = 0;
	quote->top++;
}

static void ft_push(t_stack *quote, char c)
{
	quote->top--;
	quote->stack[quote->top] = c;
}

int	open_quote(char *line)
{
	t_stack	quote;
	int	checker_top;

	quote.top = ft_strlen(line) -1;
	checker_top = quote.top;
	quote.stack = (char *)ft_calloc(ft_strlen(line) + 1, sizeof(char));
	quote.stack[ft_strlen(line)] = 0;
	while (*line)
	{
		if (*line == '\\')
			return (1);
		if(!quote.stack[quote.top] && (*line == '\'' || *line == '\"') && *(line - 1) != '\\')
			ft_push(&quote, *line);
		else if(quote.stack[quote.top] && (*line == '\'' || *line == '\"') && *(line - 1) != '\\')
		{
			if (quote.stack[quote.top] == *line)
				ft_pop(&quote);
			else
				ft_push(&quote, *line);
		}
		line++;
	}
	if (quote.top != checker_top)
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:00:28 by saan              #+#    #+#             */
/*   Updated: 2025/07/28 20:32:18 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	flag_0_get_word(t_lexer_list *list, char *line, int *idx, int *start)
{
	char	c;

	if (is_quote(line[*idx]))
	{
		c = line[(*idx)++];
		while (line[(*idx)] != c)
			++(*idx);
	}
	if (is_cutsign(line[*idx]))
	{
		add_lexer_node(list, ft_substr(line, *start, --(*idx) - *start + 1));
		return (0);
	}
	else if (is_wspace(line[*idx]))
	{
		add_lexer_node(list, ft_substr(line, *start, --(*idx) - *start + 1));
		return (1);
	}
	return (2);
}

int	flag_1_get_word(t_lexer_list *list, char *line, int *idx, int *start)
{
	if (is_cutsign(line[*idx]) || is_wspace(line[*idx]) || is_quote(line[*idx]))
	{
		add_lexer_node(list, ft_substr(line, *start, --(*idx) - *start + 1));
		return (1);
	}
	return (0);
}

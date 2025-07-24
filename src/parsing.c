/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:18:03 by saan              #+#    #+#             */
/*   Updated: 2025/07/24 16:26:32 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_quotes(char *line, int *idx)
{
	char	quote;
	int		start;

	quote = *line;
	start = ++(*idx);
	while (line[*idx])
	{
		if (line[*idx] == quote)
			return (ft_substr(&line[start], start, *idx - start - 1));
		else
		{
			++(*idx);
			continue ;
		}
	}
}

char	*normalize_cmd(char *line)
{
	int	i;
	int	start;
	char	*res;

	res = ft_strdup("");
	i = -1;
	while (line[++i])
	{
		if (is_quote(line[i]))
		{
			res = ft_join_fa(res, get_quotes(line, &i));
			continue ;
		}
		if (is_escape(line[i]))
			continue ;
		start = i;

	}
	return (res);
}

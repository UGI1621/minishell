/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:18:03 by saan              #+#    #+#             */
/*   Updated: 2025/07/24 18:44:39 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_quotes(char *line, int *idx)
{
	char	quote;
	int		start;

	quote = line[*idx];
	start = *idx;
	while (line[++(*idx)])
	{
		if (line[*idx] == quote)
			return (ft_substr(&line[start], start + 1, *idx - start - 1));
	}
	return (NULL);
}

char	*get_word(char *line, int *idx)
{

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
			res = ft_join_fa(res, get_quotes(line, &i));
		/*
		이제 여기서 뒤에
		<, >, |, <<, >>, 가 아니면
		*/
	}
	return (res);
}

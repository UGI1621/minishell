/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:18:03 by saan              #+#    #+#             */
/*   Updated: 2025/07/19 16:55:21 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_quote(char **res, char *line, int *start, int *end)
{
	char	*temp;
	char	*substr;

	*end = *start + 1;
	while(line[*end] != '\'')
		(*end)++;
	temp = *res;
	substr = ft_substr(line, *start, *end - *start + 1);
	*res = ft_strjoin(temp, substr);
	free(temp);
	free(substr);
}

char	*normalize_cmd(char *line)
{
	char	*res;
	int	start;
	int	end;

	start = 0;
	end = 0;
	res = ft_strdup("");
	while (line[start] == ' ')
		start++;
	while (line[start])
	{
		if (line[start] == '\'')
		{
			get_quote(&res, line, &start, &end);
			start = end;
		}
		start++;
	}
	return (res);
}

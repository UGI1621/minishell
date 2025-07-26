/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:39:53 by saan              #+#    #+#             */
/*   Updated: 2025/07/27 02:55:13 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_open_quote(char *line)
{
	char	c;

	while (*line)
	{
		if (*line == '\\')
			return (write(2, "minishell: syntax error with \'\\\'\n", 33));
		if(is_quote(*line))
		{
			c = *(line++);
			if (!*line)
				return (write(2, "minishell: syntax error with open quotes\n", 41));
			while(*line && *line != c)
			{
				if (*line == '\\')
					return (write(2, "minishell: syntax error with \'\\\'\n", 33));
				line++;
			}
			if (!*line)
				return (write(2, "minishell: syntax error with open quotes\n", 41));
		}
		line++;
	}
	return (0);
}

int	is_invalid_line(char *line)
{
	if (is_open_quote(line))
		return (1);
	return (0);
}

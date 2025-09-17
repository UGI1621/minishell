/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:39:53 by saan              #+#    #+#             */
/*   Updated: 2025/09/17 13:05:59 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_open_quote(char *line)
{
	char	c;

	while (*line)
	{
		if (is_quote(*line))
		{
			c = *(line++);
			if (!*line)
				return (write(2, "minishell: syntax error with open quotes\n",
						41));
			while (*line && *line != c)
			{
				if (*line == '\\')
					return (write(2, "minishell: syntax error with \'\\\'\n",
							33));
				line++;
			}
			if (!*line)
				return (write(2, "minishell: syntax error with open quotes\n",
						41));
		}
		line++;
	}
	return (0);
}

static int	is_bs_sc(char *line)
{
	while (*line)
	{
		if (*line == '\\')
			return (write(2, "minishell: syntax error with \'\\\'\n", 33));
		if (*line == ';')
			return (write(2, "minishell: syntax error with \';\'\n", 33));
		line++;
	}
	return (0);
}

int	is_invalid_line(char *line)
{
	if (is_open_quote(line))
	{
		g_sigs.exit_code = 2;
		return (1);
	}
	if (is_bs_sc(line))
	{
		g_sigs.exit_code = 2;
		return (1);
	}
	return (0);
}

int	is_invalid_env_naming_rule(char *str)
{
	if (str[0] == '_')
		return (0);
	if (!ft_isalpha(str[0]))
		return (1);
	if (str[0] == '=')
		return (1);
	if (ft_isdigit(str[0]))
		return (1);
	return (0);
}

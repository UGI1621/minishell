/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:07:22 by saan              #+#    #+#             */
/*   Updated: 2025/09/04 05:04:32 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_no_extend(char *line, int heredoc_fd)
{
	int	i;

	i = -1;
	while (line[++i])
		write(heredoc_fd, &line[i], 1);
	write(heredoc_fd, "\n",1);
}

static void	write_extend(char *line, int heredoc_fd)
{
	char	*res;
	char	*temp;
	int		i;
	int		s;

	i = -1;
	s = 0;
	while(line[++i])
	{
		if (line[i] != '$')
			write(heredoc_fd, &line[i], 1);
		else
		{
			s = i;
			while(line[i] && !is_quote(line[i]) && !is_wspace(line[i]))
				i++;
			temp = ft_substr(line, s + 1, i -s);
			write(heredoc_fd, getenv(temp), ft_strlen(getenv(temp)));
			free(temp);
		}
	}
	write(heredoc_fd, "\n", 1);
}

void	heredoc_proc(char *delimiter, int heredoc_fd, int quote_flag)
{
	char	*line;
	char	*temp;

	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		if (quote_flag)
			write_no_extend(line, heredoc_fd);
		else
			write_extend(line, heredoc_fd);
		free(line);
	}
	free(delimiter);
}

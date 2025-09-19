/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:07:22 by saan              #+#    #+#             */
/*   Updated: 2025/09/20 01:08:33 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_no_extend(char *line, int heredoc_fd)
{
	int	i;

	i = -1;
	while (line[++i])
		write(heredoc_fd, &line[i], 1);
	write(heredoc_fd, "\n", 1);
}

void	write_extra_sigs(char *line, int *i, int heredoc_fd)
{
	(*i)++;
	if (!line[(*i)])
		write(heredoc_fd, "$", 1);
	else if (line[(*i)] == '$')
		(*i)++;
}

static void	write_extend(char *line, int hf, t_env_list *e)
{
	int	i;
	int	s;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			if (line[i + 1] == '$' || !line[i + 1])
			{
				write_extra_sigs(line, &i, hf);
				continue ;
			}
			s = i++;
			while (line[i] && !is_wspace(line[i]) && !is_quote(line[i])
				&& line[i] != '$' && line[i] != '=')
				i++;
			ft_putstr_fd(cal_quotes(ft_substr(line, s, i - s), 1, e), hf);
			i--;
		}
		else
			write(hf, &line[i], 1);
		i++;
	}
	write(hf, "\n", 1);
}

static void	print_warning(char *delimiter)
{
	if (g_exit_code == 130)
	{
		set_sigs();
		return ;
	}
	ft_putstr_fd("minishell: warning: here-document ", 2);
	ft_putstr_fd("delimited by end-of-file ", 2);
	ft_putstr_fd("(wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putendl_fd("')", 2);
}

void	heredoc_proc(char *delimiter, int heredoc_fd, int is_quote,
		t_env_list *my_env)
{
	char	*line;

	set_sigs_heredoc();
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			print_warning(delimiter);
			break ;
		}
		if (!ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		if (is_quote)
			write_no_extend(line, heredoc_fd);
		else
			write_extend(line, heredoc_fd, my_env);
		free(line);
	}
	set_sigs();
}

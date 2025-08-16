/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_proc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 00:26:09 by saan              #+#    #+#             */
/*   Updated: 2025/08/16 12:45:05 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_iredir(t_lexer_list *res, char *line, int *idx)
{
	int	s;

	if (line[*idx + 1] != '<')
		add_lexer_node(res, ft_strdup("<"));
	else if (line[*idx + 1] == '<')
		return (get_word_redir(res, line, idx, "<<"));
	return (0);
}

static int	get_oredir(t_lexer_list *res, char *line, int *idx)
{
	int	s;

	if (line[*idx + 1] != '>')
		add_lexer_node(res, ft_strdup(">"));
	else if (line[*idx + 1] == '>')
		return (get_word_redir(res, line, idx, ">>"));
	return (0);
}

static void	get_word(t_lexer_list *list, char *line, int *idx)
{
	char	*temp;
	char	quote;

	quote = 0;
	temp = ft_strdup("");
	while (line[(*idx)])
	{
		temp = append_char(temp, line[(*idx)]);
		if (is_quote(line[(*idx)]))
		{
			quote = line[(*idx)++];
			while (line[(*idx)] != quote)
			{
				temp = append_char(temp, line[(*idx)]);
				(*idx)++;
			}
			temp = append_char(temp, line[(*idx)]);
		}
		++(*idx);
		if (is_wspace(line[(*idx)]) || is_cutsign(line[(*idx)]))
			break ;
	}
	add_lexer_node(list, temp);
}

int	ft_lexing_proc(t_lexer_list *res, char *line, int *i)
{
	if (line[*i] == '|')
		add_lexer_node(res, ft_strdup("|"));
	else if (line[*i] == '<')
	{
		return (get_iredir(res, line, i));
	}
	else if (line[*i] == '>')
	{
		return (get_oredir(res, line, i));
	}
	else if (!is_wspace(line[*i]))
	{
		get_word(res, line, i);
		(*i)--;
	}
	return (0);
}

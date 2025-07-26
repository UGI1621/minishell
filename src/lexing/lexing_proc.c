/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_proc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 00:26:09 by saan              #+#    #+#             */
/*   Updated: 2025/07/27 06:24:08 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_quotes(char *line, int *idx)
{
	char	quote;
	int		start;
	int		end;
	char	*res;

	quote = line[*idx];
	start = (*idx)++;
	while (line[(*idx)])
	{
		if (line[*idx] == quote)
			return (ft_substr(line, start, *idx - start + 1));
		(*idx)++;
	}
	return (NULL);
}

static void	get_iredir(t_lexer_list *res, char *line, int *idx)
{
	int	s;

	if (line[*idx + 1] != '<')
		add_lexer_node(res, ft_strdup("<"));
	else if (line[*idx + 1] == '<')
	{
		add_lexer_node(res, ft_strdup("<<"));
		*idx += 2;
		s = *idx;
		while(line[*idx] && !is_cutsign(line[*idx]))
		{
			if (is_quote(line[*idx]))
			{
				free(get_quotes(line, idx));
				break ;
			}
			++(*idx);
		}
		add_lexer_node(res, ft_substr(line, s, *idx - s + 1));
	}
}

static void	get_oredir(t_lexer_list *res, char *line, int *idx)
{
	int	s;

	if (line[*idx + 1] != '>')
		add_lexer_node(res, ft_strdup(">"));
	else if (line[*idx + 1] == '>')
	{
		add_lexer_node(res, ft_strdup(">>"));
		*idx += 2;
		s = *idx;
		while(line[*idx] && !is_cutsign(line[*idx]))
		{
			if (is_quote(line[*idx]))
			{
				free(get_quotes(line, idx));
				break ;
			}
			++(*idx);
		}
		add_lexer_node(res, ft_substr(line, s, *idx - s + 1));
	}
}

static void	get_word(t_lexer_list *list, char *line, int *idx)
{
	int	start;
	char	c;

	start = (*idx);
	while (line[*idx])
	{
		if (is_cutsign(line[*idx]))
		{
			--(*idx);
			add_lexer_node(list, ft_substr(line, start, *idx - start + 1));
			break ;
		}
		(*idx)++;
	}
	if (!line[*idx])
		add_lexer_node(list, ft_substr(line, start, *idx - start + 1));
}

t_lexer_list	*ft_lexing(char *line)
{
	t_lexer_list	*res;
	int				i;
	int				start;

	i = -1;
	res = (t_lexer_list *)ft_calloc(1, sizeof(t_lexer_list));
	res->head = NULL;
	res->tail = NULL;
	while(line[++i])
	{
		if (is_quote(line[i]))
			add_lexer_node(res, get_quotes(line, &i));
		else if (line[i] == '|')
			add_lexer_node(res, ft_strdup("|"));
		else if (line[i] == '<')
			get_iredir(res, line, &i);
		else if (line[i] == '>')
			get_oredir(res, line, &i);
		else if (line[i] != ' ')
			get_word(res, line, &i);
	}
	return (res);
}

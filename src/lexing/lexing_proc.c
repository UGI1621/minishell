/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_proc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 00:26:09 by saan              #+#    #+#             */
/*   Updated: 2025/08/09 16:47:02 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_iredir(t_lexer_list *res, char *line, int *idx)
{
	int	s;

	if (line[*idx + 1] != '<')
		add_lexer_node(res, ft_strdup("<"));
	else if (line[*idx + 1] == '<')
	{
		if (line[*idx + 2] == '<')
			return (invalid_token(res, '<'));
		add_lexer_node(res, ft_strdup("<<"));
		*idx += 2;
		while (is_wspace(line[*idx]))
			++(*idx);
		s = *idx;
		while(line[*idx] && !is_cutsign(line[*idx]))
		{
			if (is_wspace(line[*idx]))
			{
				add_lexer_node(res, ft_substr(line, s, *idx - s));
				return (0);
			}
			++(*idx);
		}
		add_lexer_node(res, ft_substr(line, s, *idx - s + 1));
	}
	return (0);
}

static int	get_oredir(t_lexer_list *res, char *line, int *idx)
{
	int	s;

	if (line[*idx + 1] != '>')
		add_lexer_node(res, ft_strdup(">"));
	else if (line[*idx + 1] == '>')
	{
		if (line[*idx + 2] == '>')
			return (invalid_token(res, '>'));
		add_lexer_node(res, ft_strdup(">>"));
		*idx += 2;
		while (is_wspace(line[*idx]))
			++(*idx);
		s = *idx;
		while(line[*idx] && !is_cutsign(line[*idx]))
		{
			if (is_wspace(line[*idx]))
			{
				add_lexer_node(res, ft_substr(line, s, *idx - s));
				return (0);
			}
			++(*idx);
		}
		add_lexer_node(res, ft_substr(line, s, *idx - s + 1));
	}
	return (0);
}

// static void	get_word(t_lexer_list *list, char *line, int *idx, int *flag)
// {
// 	int	start;
// 	int	word_flag;

// 	start = *idx;
// 	while (line[++(*idx)])
// 	{
// 		if (*flag == 0)
// 		{
// 			word_flag = flag_0_get_word(list, line, idx, &start);
// 			if (word_flag != 2)
// 			{
// 				if (word_flag == 1)
// 					*flag = 1;
// 				break ;
// 			}
// 		}
// 		else if (flag_1_get_word(list, line, idx, &start))
// 		{
// 			*flag = 0;
// 			break ;
// 		}
// 	}
// 	if (!line[*idx])
// 		add_lexer_node(list, ft_substr(line, start, *idx - start + 1));
// }

static void	get_word(t_lexer_list *list, char *line, int *idx, char flag)
{
	int	start;

	start = (*idx);
	while (line[++(*idx)])
	{
		if (flag)
		{
			if (is_cutsign(line[*idx]) || line[*idx] == flag)
			{
				add_lexer_node(list, ft_substr(line, start, *idx - start));
				break ;
			}
		}
		else
		{
			if (is_cutsign(line[*idx]) || is_wspace(line[*idx]))
			{
				add_lexer_node(list, ft_substr(line, start, *idx - start));
				break ;
			}
		}
	}
	if (!line[*idx])
		add_lexer_node(list, ft_substr(line, start, *idx - start + 1));
}

int	ft_lexing_proc(t_lexer_list *res, char *line, int *i)
{
	char	flag;

	flag = 0;
	if (is_quote(line[*i]))
		flag = line[*i];
	if (line[*i] == '|')
		add_lexer_node(res, ft_strdup("|"));
	else if (line[*i] == '<')
		return (get_iredir(res, line, i));
	else if (line[*i] == '>')
		return (get_oredir(res, line, i));
	else if (line[*i] != ' ')
		get_word(res, line, i, flag);
	return (0);
}

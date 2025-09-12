/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotting_lexer_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 04:02:38 by saan              #+#    #+#             */
/*   Updated: 2025/09/12 09:46:37 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*list_to_str(t_lexer_list *list)
{
	t_lexer_node	*node;
	char	*str;

	node = list->head;
	str = ft_strdup("");
	while (node)
	{
		str = ft_strjoin_af(str, ft_strdup(node->str));
		str = append_char(str, ' ');
		node = node->next;
	}
	return (str);
}

static char	*get_quotes(char *str, int *i)
{
	char	quote;
	int	start;

	quote = str[(*i)];
	start = ++(*i);
	while(str[(*i)] && str[(*i)] != quote)
		(*i)++;
	return (ft_substr(str, start, (*i) - start));
}

char	*remove_quotes(char *str)
{
	char	*res;
	int	i;

	i = 0;
	res = ft_strdup("");
	while (str[i])
	{
		if (is_quote(str[i]))
			res = ft_strjoin_af(res, get_quotes(str, &i));
		else
			res = append_char(res, str[i]);
		if (!str[i])
			break;
		i++;
	}
	free(str);
	return (res);
}

void	quotting_lexer_list(t_lexer_list **list)
{
	t_lexer_node	*node;
	t_lexer_list *res;
	char	*str;
	int	i;

	str = list_to_str((*list));
	i = -1;
	init_lexer_list(&res);
	while (str[++i])
		ft_lexing_proc(res, str, &i);
	node = res->head;
	while (node)
	{
		if (node->prev && !ft_strcmp(node->prev->str, "<<"))
		{
			node = node->next;
			continue ;
		}
		node->str = remove_quotes(node->str);
		node = node->next;
	}
	free(str);
	free_lexer_list(*list);
	(*list) = res;
}

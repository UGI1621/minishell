/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:00:28 by saan              #+#    #+#             */
/*   Updated: 2025/09/17 12:53:18 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_char(char *str, char c)
{
	int		len;
	char	*res;
	int		i;

	len = 0;
	while (str && str[len])
		len++;
	res = (char *)ft_calloc(len + 2, sizeof(char));
	i = 0;
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = c;
	res[i + 1] = 0;
	free(str);
	return (res);
}

int	get_word_redir(t_lexer_list *res, char *line, int *idx, char *sig)
{
	char	*temp;
	char	quote;

	if (line[*idx + 2] == line[*idx + 1])
		return (invalid_token(res, line[*idx + 1]));
	add_lexer_node(res, ft_strdup(sig));
	*idx += 2;
	while (is_wspace(line[*idx]))
		++(*idx);
	temp = ft_strdup("");
	while (line[(*idx)] && !is_wspace(line[*idx]) && !is_cutsign(line[*idx]))
	{
		if (is_quote(line[(*idx)]))
		{
			quote = line[*idx];
			temp = append_char(temp, line[(*idx)]);
			while (line[++(*idx)] != quote)
				temp = append_char(temp, line[(*idx)]);
		}
		temp = append_char(temp, line[(*idx)]);
		(*idx)++;
	}
	add_lexer_node(res, temp);
	--(*idx);
	return (0);
}
